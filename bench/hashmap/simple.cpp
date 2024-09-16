#include <benchmark/benchmark.h>

#include "random.h"
#include "container/hashmap.h"
#include "absl/container/flat_hash_map.h"

constexpr size_t LS = 1u << 12u;

template<typename T>
static void BM_abseil_flat_hash_map(benchmark::State &state) {
	static std::vector<T> data;
	absl::flat_hash_map<int, std::string> map1;

	for (auto _: state) {
		for (size_t i = 0; i < data.size(); ++i) {
			cnt[data[i]] += 1;
		}
		benchmark::ClobberMemory();
	}
}


#ifdef USE_AVX2
template<typename T>
static void BM_histogram_avx2(benchmark::State &state) {
	static std::vector<T> data;
	generate_data(data, state.range(0));
	for (auto i = 0; i < state.range(0); ++i) { data[i] = data[i] & 0xFF; }


	for (auto _: state) {
		avx2_histogram_u32(cnt, data.data(), state.range(0));
		benchmark::ClobberMemory();
	}
}
BENCHMARK(BM_histogram_avx2<uint32_t>)->RangeMultiplier(2)->Range(32, LS);
#endif

BENCHMARK(BM_stupid_histogram<uint8_t>)->RangeMultiplier(2)->Range(32, LS);

BENCHMARK_MAIN();
