/**
 * @file EventQueue_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-28
 *
 * @copyright Copyright (c) 2018
 *
 */

#include"gtest/gtest.h"
#include"EventQueue.h"

//EventQueue();
TEST(EventQueue_Constructor_Test, TEST01) {
	EXPECT_NO_THROW(EventQueue<bool> e;);
}

//Event();
TEST(EventQueue_Constructor_Test, TEST02) {
	EXPECT_NO_THROW(Evented<bool>* events;);
}

//Event();
TEST(EventQueue_Go_Test, TEST01) {
	std::unordered_set<Evented<bool>*> empty = {};
	Evented<bool>* event4 = new Evented<bool>();
	EXPECT_EQ(1, event4->go().size());
	EXPECT_TRUE(event4->go().empty());
}

//Event();
TEST(EventQueue_Go_Test, TEST02) {
	std::unordered_set<Evented<bool>*> empty = {};
	Evented<bool>* event1 = new Evented<bool>;
	Evented<bool>* event2 = new Evented<bool>;
	Evented<bool>* event3 = new Evented<bool>;
	std::unordered_set<Evented<bool>*> event_ins = {event1, event2};
	std::unordered_set<Evented<bool>*> event_outs = { event3 };
	Evented<bool>* event4 = new Evented<bool>(event_ins,event_outs);
	EXPECT_EQ(1,event4->go().size());
}

//Event();
TEST(EventQueue_Add_Test, TEST01) {
	std::unordered_set<Evented<bool>*> empty = {};
	EventQueue<bool> e;
	Evented<bool>* event1 = new Evented<bool>;
	Evented<bool>* event2 = new Evented<bool>;
	Evented<bool>* event3 = new Evented<bool>;
	std::unordered_set<Evented<bool>*> event_ins = { event1, event2 };
	std::unordered_set<Evented<bool>*> event_outs = { event3 };
	Evented<bool>* event4 = new Evented<bool>(event_ins, event_outs);
	EXPECT_NO_THROW(e.add(0, event1););
}

//Event();
TEST(EventQueue_Add_Test, TEST02) {
	std::unordered_set<Evented<bool>*> empty = {};
	EventQueue<bool> e;
	Evented<bool>* event1 = new Evented<bool>;
	Evented<bool>* event2 = new Evented<bool>;
	Evented<bool>* event3 = new Evented<bool>;
	std::unordered_set<Evented<bool>*> event_ins = { event1, event2 };
	std::unordered_set<Evented<bool>*> event_outs = { event3 };
	Evented<bool>* event4 = new Evented<bool>(event_ins, event_outs);
	EXPECT_NO_THROW(e.add(0, event1););
}

//Event();
TEST(EventQueue_Add_Test, TEST03) {
	std::unordered_set<Evented<bool>*> empty = {};
	EventQueue<bool> e;
	Evented<bool>* event1 = new Evented<bool>;
	Evented<bool>* event2 = new Evented<bool>;
	Evented<bool>* event3 = new Evented<bool>;
	std::unordered_set<Evented<bool>*> event_ins = { event1, event2 };
	std::unordered_set<Evented<bool>*> event_outs = { event3 };
	Evented<bool>* event4 = new Evented<bool>(event_ins, event_outs);
	std::pair<size_t, Evented<bool>*> pair1 = {0,event1};
	std::pair<size_t, Evented<bool>*> pair2 = { 0,event2 };
	std::pair<size_t, Evented<bool>*> pair3 = { 1,event4 };
	std::pair<size_t, Evented<bool>*> pair4 = { 2,event3 };
	std::set<std::pair<size_t, Evented<bool>*>> set = {pair1, pair2, pair3, pair4};
	EXPECT_NO_THROW(e.add(set););
}

//Event();
TEST(EventQueue_Process_Test, TEST01) {
	std::unordered_set<Evented<bool>*> empty = {};
	EventQueue<bool> e;
	Evented<bool>* event1 = new Evented<bool>;
	Evented<bool>* event2 = new Evented<bool>;
	Evented<bool>* event3 = new Evented<bool>;
	std::unordered_set<Evented<bool>*> event_ins = { event1, event2 };
	std::unordered_set<Evented<bool>*> event_outs = { event3 };
	Evented<bool>* event4 = new Evented<bool>(event_ins, event_outs);
	std::pair<size_t, Evented<bool>*> pair1 = { 0,event1 };
	std::pair<size_t, Evented<bool>*> pair2 = { 0,event2 };
	std::pair<size_t, Evented<bool>*> pair3 = { 1,event4 };
	std::pair<size_t, Evented<bool>*> pair4 = { 2,event3 };
	std::set<std::pair<size_t, Evented<bool>*>> set = { pair1, pair3, pair4 };
	e.add(set);
	EXPECT_NO_THROW(e.process(););
}

//Event();
TEST(EventQueue_Process_Test, TEST02) {
	std::unordered_set<Evented<bool>*> empty = {};
	EventQueue<bool> e;
	Evented<bool>* event1 = new Evented<bool>;
	Evented<bool>* event2 = new Evented<bool>;
	Evented<bool>* event3 = new Evented<bool>;
	std::unordered_set<Evented<bool>*> event_ins = { event1, event2 };
	std::unordered_set<Evented<bool>*> event_outs = { event3 };
	Evented<bool>* event4 = new Evented<bool>(event_ins, event_outs);
	std::pair<size_t, Evented<bool>*> pair1 = { 0,event1 };
	std::pair<size_t, Evented<bool>*> pair2 = { 0,event2 };
	std::pair<size_t, Evented<bool>*> pair3 = { 1,event4 };
	std::pair<size_t, Evented<bool>*> pair4 = { 2,event3 };
	std::set<std::pair<size_t, Evented<bool>*>> set = { pair1, pair2, pair4, pair3 };
	e.add(set);
	EXPECT_ANY_THROW(e.process(););
}
