#include <benchmark/benchmark.h>
#include "absl/container/flat_hash_map.h"

#include "container/hashmap.h"
#include "container/imap.h"

constexpr size_t LS = 1u << 12u;

template<typename T>
static void BM_abseil_flat_hash_map(benchmark::State &state) {
    absl::flat_hash_map<T, T> map;

    for (auto _: state) {
        for (int64_t i = 0; i < state.range(0); ++i) {
            map[i] = i;
        }
        benchmark::ClobberMemory();

        for (int64_t i = 0; i < state.range(0); ++i) {
            auto t = map.find(i);
            (void)t;
        }
        benchmark::ClobberMemory();

        for (int64_t i = 0; i < state.range(0); ++i) {
            map.erase(i);
        }
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_abseil_flat_hash_map<uint32_t>)->RangeMultiplier(2)->Range(32, LS);
BENCHMARK(BM_abseil_flat_hash_map<uint64_t>)->RangeMultiplier(2)->Range(32, LS);

template<typename T>
static void BM_std_unordered_map(benchmark::State &state) {
	std::unordered_map<T, T> map;

	for (auto _: state) {
		for (int64_t i = 0; i < state.range(0); ++i) {
            map[i] = i;
		}
        benchmark::ClobberMemory();

		for (int64_t i = 0; i < state.range(0); ++i) {
            auto t = map.find(i);
            (void)t;
        }
        benchmark::ClobberMemory();

        for (int64_t i = 0; i < state.range(0); ++i) {
             map.erase(i);
        }
		benchmark::ClobberMemory();
	}
}
BENCHMARK(BM_std_unordered_map<uint32_t>)->RangeMultiplier(2)->Range(32, LS);
BENCHMARK(BM_std_unordered_map<uint64_t>)->RangeMultiplier(2)->Range(32, LS);

static void BM_imap(benchmark::State &state) {
    imap_tree_t tree(state.range(0));
    uint32_t *slot;
    for (auto _: state) {
        for (int64_t i = 0; i < state.range(0); ++i) {
            slot = tree.assign(i);
            (void)slot;
        }
        benchmark::ClobberMemory();

        for (int64_t i = 0; i < state.range(0); ++i) {
            slot = tree.lookup(i);
            (void)slot;
        }
        benchmark::ClobberMemory();

        for (int64_t i = 0; i < state.range(0); ++i) {
            tree.remove(i);
        }
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_imap)->RangeMultiplier(2)->Range(32, LS);


BENCHMARK_MAIN();
