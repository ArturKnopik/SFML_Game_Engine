#pragma

namespace KOD
{
	class IUIHandler
	{

	public:
		IUIHandler();
		virtual void update(size_t dt) = 0;
	};
}