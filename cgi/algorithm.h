#pragma once

#include <stack>
#include <chrono>
#include <functional>

namespace cgi
{
	namespace algorithm
	{
		// Shuffles a stack
		template<class StackType>
		static void Shuffle(std::stack<StackType>& stack)
		{
			std::stack<StackType> a, b, c, d;
			int times = rand() % 6 + 5;

			for (int i = 0; i < times; i++)
			{
				int go = rand() % 4;

				while (!stack.empty())
				{
					switch (go)
					{
					case 0:
						a.push(stack.top());
						break;
					case 1:
						b.push(stack.top());
						break;
					case 2:
						c.push(stack.top());
						break;
					case 3:
						d.push(stack.top());
						break;
					}

					stack.pop();
					go = rand() % 4;
				}

				while (!a.empty())
				{
					stack.push(a.top());
					a.pop();
				}


				while (!c.empty())
				{
					stack.push(c.top());
					c.pop();
				}

				while (!b.empty())
				{
					stack.push(b.top());
					b.pop();
				}

				while (!d.empty())
				{
					stack.push(d.top());
					d.pop();
				}
			}
		}

		// DO NOT USE
		// NOT CONFIRMED IF WORKING
		long long PerformanceTest(std::function<void(void)> function)
		{
			auto start = std::chrono::steady_clock::now();
			function();
			auto end = std::chrono::steady_clock::now();
			return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		}

	}
}