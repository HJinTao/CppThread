PP := g++

ThreadSimple : ThreadSimple.cpp
	$(PP) -std=c++11 -pthread $^ -o $@
	./$@
	rm -f $@


ThreadFault : ThreadFault.cpp
	$(PP) -std=c++11 -pthread $^ -o $@
	./$@
	rm -f $@

ThreadDateRace : ThreadDateRace.cpp
	$(PP) -std=c++11 -pthread $^ -o $@
	./$@
	rm -f $@

ThreadDeadlock : ThreadDeadlock.cpp
	$(PP) -std=c++11 -pthread $^ -o $@
	./$@
	rm -f $@

ThreadCallOnce : ThreadCallOnce.cpp
	$(PP) -std=c++11 -pthread $^ -o $@
	./$@
	rm -f $@

temp : temp.cpp
	$(PP) -std=c++11 -pthread $^ -o $@
	./$@
	rm -f $@

ThreadPool : ThreadPool.cpp
	$(PP) -std=c++11 -pthread $^ -o $@
	./$@
	rm -f $@

.PHONY : clean

clean:
	-rm -f Thread