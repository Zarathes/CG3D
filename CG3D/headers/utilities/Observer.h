#pragma once

namespace cg3d
{
	// Forward Declaration
	struct Event;

	class Observer
	{
	public:
		virtual void onNotify(Event& event) = 0;
	};
}