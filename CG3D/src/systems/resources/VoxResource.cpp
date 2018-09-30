#include "systems\resources\VoxResource.h"

// Additional includes
#include <string>
#include <algorithm>

// Namespaces
using namespace cg3d;

// Strucs
struct SortByMaterialID
{
	inline bool operator() (const VoxelData& voxel1, const VoxelData& voxel2)
	{
		return (voxel1._matId < voxel2._matId);
	}
};

VoxResource::VoxResource()
	: Resource(
		ResourceType::RecourceVox
		, "vox_models\\"
	)
	, _materials(std::vector<MaterialData>(256))
{
	_dictionary["_diffuse"] = MaterialType::TypeDiffuse;
	_dictionary["_metal"] = MaterialType::TypeMetal;
	_dictionary["_glass"] = MaterialType::TypeGlass;
	_dictionary["_emit"] = MaterialType::TypeEmit;

}
VoxResource::~VoxResource()
{
}

bool VoxResource::loadResource(uint64_t id, const char* basePath, const char* filePath)
{
	_id = id;
	_path = filePath;

	std::string path = basePath;
	path.append(_subDir);
	path.append(filePath);

	std::ifstream stream;
	if (!openFileStream(&stream, path))
		return false;
	
	magicNumber(&stream);

	try
	{
		readChunk(&stream);
	}
	catch (const std::exception&)
	{
		printf("Unexpected end of file reached!");
		return false;
	}
	stream.close();

	std::sort(_model._voxelArray.begin(), _model._voxelArray.end(), SortByMaterialID());
	

	return true;
}

bool VoxResource::openFileStream(std::ifstream* stream, std::string filePath)
{
	size_t found = filePath.find_last_of("\\");
	std::string fileName = filePath.substr(found + 1);
	found = filePath.find_last_of(".");
	fileName = filePath.substr(0, found);
	stream->open(filePath, std::ios::in | std::ios::binary);
	if (stream->is_open())
	{
		//printf("File %s opened \n", fileName.c_str());
		_name = fileName;
		return true;
	}
	else
	{
		printf("File %s not found \n", fileName.c_str());
		return false;
	}

}

/* File Structure : RIFF style
------------------------------------------------------------------------------- -
# Bytes | Type | Value
------------------------------------------------------------------------------- -
1x4 | char | id 'VOX ' : 'V' 'O' 'X' 'space', 'V' is first
4 | int  | version number : 150
------------------------------------------------------------------------------- */
int VoxResource::magicNumber(std::ifstream* stream)
{
	char magicNumber[5] = {};
	for (int i = 0; i < 4; i++)
	{
		stream->get(magicNumber[i]);
	}
	// Manually add null terminator
	magicNumber[4] = 0;
	int	versionNumber;
	stream->read((char*)&versionNumber, 4);
	//printf("Magic number: %s%i \n", magicNumber, versionNumber);
	return versionNumber;
}

/* Chunk Structure
-------------------------------------------------------------------------------
# Bytes  | Type       | Value
-------------------------------------------------------------------------------
1x4      | char       | chunk id
4        | int        | num bytes of chunk content (N)
4        | int        | num bytes of children chunks (M)
N        |            | chunk content
M        |            | children chunks
------------------------------------------------------------------------------- */
uint32_t VoxResource::readChunk(std::ifstream* stream)
{
	// Chunk ID
	std::vector<char> id = std::vector<char>(4);
	stream->read(&id[0], 4);
	std::string chunkID{ id.begin(), id.end() };
	//printf("Chunk ID: %s\n", chunkID.c_str());

	int numBytesOfChunkContent;
	stream->read((char*)&numBytesOfChunkContent, 4);
	//printf("Chunk content size: %i bytes\n", numBytesOfChunkContent);
	int numBytesOfChildrenChunks;
	stream->read((char*)&numBytesOfChildrenChunks, 4);
	//printf("Children chunk content size: %i bytes\n", numBytesOfChildrenChunks);

	switch (hash(chunkID.c_str()))
	{
	//case hash("PACK"):
	//	//ReadPACKContent(stream, model);
	//	break;
	case hash("SIZE"):
		readSIZEContent(stream);
		break;
	case hash("XYZI"):
		readXYZIContent(stream);
		break;
	case hash("RGBA"):
		readRGBAContent(stream);
		break;
	case hash("MATL"):
		readMATLContent(stream);
		break;
	default:
		for (int i = 0; i < numBytesOfChunkContent; i++)
		{
			if (stream->eof())
				throw std::exception();
			stream->get();
		}
		break;
	}

	while (numBytesOfChildrenChunks > 0)
	{
		numBytesOfChildrenChunks -= readChunk(stream);
	}

	return 12 + numBytesOfChunkContent + numBytesOfChildrenChunks;
}

/* Chunk id 'SIZE' : model size
------------------------------------------------------------------------------ -
# Bytes | Type | Value
------------------------------------------------------------------------------ -
4 | int | size x
4 | int | size z : gravity direction
4 | int | size y
------------------------------------------------------------------------------ - */
void VoxResource::readSIZEContent(std::ifstream* stream)
{
	int32_t x, z, y;
	stream->read((char*)&x, 4);
	stream->read((char*)&z, 4);
	stream->read((char*)&y, 4);

	_model._size = { x, y, z };
	//printf("Model size: width(x) %i, depth(z) %i, height(y) %i \n", x, y, z);
}

/* Chunk id 'XYZI' : model voxels
------------------------------------------------------------------------------ -
# Bytes | Type | Value
------------------------------------------------------------------------------ -
4	  | int | numVoxels(N)
4 x N | int | (x, z, y, colorIndex) : 1 byte for each component
------------------------------------------------------------------------------ - */
void VoxResource::readXYZIContent(std::ifstream* stream)
{
	uint32_t voxelCount;
	stream->read((char*)&voxelCount, 4);
	_model._voxCount = voxelCount;
	//printf("Number of voxels: %i\n", voxelCount);

	for (size_t i = 0; i < voxelCount; i++)
	{
		int32_t tmp;
		stream->read((char*)&tmp, 4);

		VoxelData data = VoxelData();
		data._position = { ((unsigned char *)(&tmp))[0], ((unsigned char*)(&tmp))[2], ((unsigned char *)(&tmp))[1] };
		data._position.x = (_model._size.x - 1) - data._position.x;
		data._id = _model._voxelArray.size();
		data._matId = ((unsigned char *)(&tmp))[3];
		data._matId -= 1;
		_model._voxelArray.push_back(data);
		//printf("Vox #%07d - x %03d, z %03d, y %03d, Material ID %03d\n", static_cast<int>(i), data._position.x, data._position.y, data._position.z, data._matId);
	}
}

/* Chunk id 'RGBA' : palette
------------------------------------------------------------------------------ -
# Bytes  | Type       | Value
------------------------------------------------------------------------------ -
4 x 256  | int        | (R, G, B, A) : 1 byte for each component
| * <NOTICE>
| * color [0-254] are mapped to palette index [1-255], e.g :
|
| for ( int i = 0; i <= 254; i++ ) {
|     palette[i + 1] = ReadRGBA();
| }
------------------------------------------------------------------------------ - */
void VoxResource::readRGBAContent(std::ifstream* stream)
{
	for (size_t i = 0; i <= 255; i++)
	{
		uint32_t tmp;
		stream->read((char*)&tmp, 4);
		uint8_t red, green, blue, alpha;
		red = ((unsigned char *)(&tmp))[0];
		green = ((unsigned char *)(&tmp))[1];
		blue = ((unsigned char *)(&tmp))[2];
		alpha = ((unsigned char *)(&tmp))[3];
		//printf("Palette #%03d - Red %03d, Green %03d, Blue %03d, Alpha %03d\n", static_cast<int>(i), red, green, blue, alpha);

		MaterialData data = MaterialData();
		data._matId = static_cast<uint32_t>(i);
		data._diffuseColor = { red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f };
		_materials[i] = data;
	}
}

/* Chunk id 'MATL' : material
------------------------------------------------------------------------------ -
=================================
(a) STRING type

int32   : buffer size (in bytes)
int8xN	: buffer (without ending "\0")

=================================
(b) DICT type

int32	: num key-value pairs

// for each key-value pair
{
STRING	: key
STRING	: value
}xN

=================================
(4) Material Chunk : "MATL"

int32	: material id
DICT	: material properties
(_type : str) _diffuse, _metal, _glass, _emit
(_weight : float) range 0 ~ 1
(_rough : float)
(_spec : float)
(_ior : float)
(_att : float)
(_flux : float)
(_glow : float)
(_unit)
(_plastic)
------------------------------------------------------------------------------ - */
void VoxResource::readMATLContent(std::ifstream* stream)
{
	uint32_t id;
	stream->read((char*)&id, sizeof(uint32_t));
	//printf("MATL Id: %03i\n", id);

	MaterialData data = _materials[id];
	//assert(data._matId == id);

	uint32_t numProperties;
	stream->read((char*)&numProperties, sizeof(uint32_t));
	//printf("MATL number of properties: %i\n", numProperties);

	std::vector<std::pair<std::string, std::string>> properties = std::vector<std::pair<std::string, std::string>>(numProperties);
	for (size_t i = 0; i < numProperties; i++)
	{
		//Key
		int32_t keySize;
		stream->read((char*)&keySize, sizeof(int32_t));
		std::vector<char> keyBuffer = std::vector<char>(keySize);
		stream->read(&keyBuffer[0], keySize * sizeof(int8_t));
		std::string key{ keyBuffer.begin(), keyBuffer.end() };

		//Value
		int32_t valueSize;
		stream->read((char*)&valueSize, sizeof(int32_t));
		std::vector<char> valueBuffer = std::vector<char>(valueSize);
		stream->read(&valueBuffer[0], valueSize * sizeof(int8_t));
		std::string value{ valueBuffer.begin(), valueBuffer.end() };
		properties[i] = std::make_pair(key, value);
		//printf("MATL Property #%i: %s %s\n", static_cast<int>(i), key.c_str(), value.c_str());

		switch (hash(key.c_str()))
		{
		case hash("_type"):
			data._type = static_cast<MaterialType>(_dictionary[value]);
			break;
		case hash("_weight"):
			data._propWeight = std::stof(value);
			break;
		case hash("_rough"):
			data._propRough = std::stof(value);
			break;
		case hash("_spec"):
			data._propSpecular = std::stof(value);
			break;
		case hash("_ior"):
			data._propRefraction = std::stof(value);
			break;
			case hash("_att"):
			data._propAttentuate = std::stof(value);
			break;
		case hash("_flux"):
			data._propFlux = std::stof(value);
			break;
		case hash("_glow"):
			data._propGlow = std::stof(value);
			break;
		case hash("_unit"):
			data._propUnit = std::stof(value);
			break;
			case hash("_plastic"):
			data._propPlastic = std::stof(value);
			break;
		default:
			break;
		}
	}

	_materials[id] = data;
}