/*
			This file is part of:
				TmingEngine
			https://github.com/xiaomingfun/TmingEngine

   Copyright 2018 - 2020 TmingEngine

   File creator: littleblue

   TmingEngine is open-source software and you can redistribute it and/or modify
   it under the terms of the License; besides, anyone who use this file/software must include this copyright announcement.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef TmingEngine_Editor_UI_Profiler_hpp
#define TmingEngine_Editor_UI_Profiler_hpp

#include <iostream>
#include <string>

#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "Plantform/Windows/Widget.h"

#include "ImNodes/ImNodes.h"
#include "ImNodes/ImNodesEz.h"

namespace TmingEngine
{
	class Profiler :public Widget
	{
	public:

		Profiler(Context* context)
		{
			m_title = "Profiler";
		}
		~Profiler();

		void Begin();
		void Update();
		void End();

		int ImageId;
	};
}// namespace TmingEngine

#endif /* TmingEngine_Editor_UI_Profiler_hpp */