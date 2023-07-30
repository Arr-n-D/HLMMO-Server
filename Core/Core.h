#pragma once
#include "../sentry.h"

namespace ArrND::Core {
	class Core {
		public:
			Core();
			~Core();
			void Init();


		private:
			void InitializeSentry();
	};
}
