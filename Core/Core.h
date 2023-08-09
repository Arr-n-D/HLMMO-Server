#pragma once
#include "../NetworkManager.h"
#include "../sentry.h"


	class Core {
		public:
			Core();
			~Core();
			void Initialize();
			NetworkManager GetNetworkManager();


		private:
			void InitializeSentry();
			NetworkManager networkManager;
	};
