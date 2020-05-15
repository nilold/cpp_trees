#include <functional>
#include <benchmark/benchmark.h>
#include <stack>
#include <list>
#include <vector>

struct List;

List *create_list(int);

List *reverse_recursive(List *);

List *reverse_iteratively(List *);

std::list<int> reverse_stack(List *);

std::vector<int> reverse_stack_vector(List *obj);

static void BM_iterative_reverse(benchmark::State& state) {
    auto list = create_list(100);
    for (auto _ : state)
        reverse_iteratively(list);
}

static void BM_recursive_reverse(benchmark::State& state) {
    auto list = create_list(100);
    for (auto _ : state)
        reverse_recursive(list);
}

static void BM_reverse_stack(benchmark::State& state) {
    auto list = create_list(100);
    for (auto _ : state)
        reverse_stack(list);
}

static void BM_reverse_stack_vector(benchmark::State& state) {
    auto list = create_list(100);
    for (auto _ : state)
        reverse_stack_vector(list);
}

BENCHMARK(BM_iterative_reverse);
BENCHMARK(BM_recursive_reverse);
BENCHMARK(BM_reverse_stack);
BENCHMARK(BM_reverse_stack_vector);

BENCHMARK_MAIN();

struct List {
    int m_value;

    List(int value, List *other) : m_value(value), other(other) {};
    List *other{nullptr};
};

List *create_list(int size) {
    List *prev = new List(1, nullptr);;
    for (int i = 2; i <= size; ++i) {
        List *newElement = new List(i, prev);
        prev = newElement;
    }
    return prev;
}


List *reverse_recursive(List *obj) {
    std::function<List *(List *)> rec;

    rec = [&](auto obj) -> decltype(obj) {
        if (!obj)
            return nullptr;
        if (!obj->other)
            return obj;
        auto relevantObj = rec(obj->other);
        obj->other->other = obj;
        obj->other = nullptr;
        return relevantObj;
    };

    return rec(obj);
}

List *reverse_iteratively(List *obj) {
    List *prev = obj;
    List *curr = obj->other;
    obj->other = nullptr;
    List *next;

    while (curr != nullptr) {
        next = curr->other;
        curr->other = prev;
        prev = curr;
        obj = curr;
        curr = next;
    }

    return obj;
}

std::list<int> reverse_stack(List *obj){
    std::stack<List*> stack;

    while(obj != nullptr){
        stack.push(obj);
        obj = obj->other;
    }

    std::list<int> list(stack.size());

    while(!stack.empty()){
        list.push_back(stack.top()->m_value);
        stack.pop();
    }

    return list;
}

std::vector<int> reverse_stack_vector(List *obj){
    std::stack<List*> stack;

    while(obj != nullptr){
        stack.push(obj);
        obj = obj->other;
    }

    std::vector<int> list(stack.size());

    while(!stack.empty()){
        list.push_back(stack.top()->m_value);
        stack.pop();
    }

    return list;
}
