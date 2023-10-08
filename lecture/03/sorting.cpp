#include <algorithm>
#include <climits>
#include <chrono>
#include <cstring>
#include <iostream>
#include <random>
#include <vector>

#define SIZE 100

struct HSLA {
  float hue;
  float saturation;
  float lightness;
  float alpha;
};

// Calculates the luminosity of an HSLA pixel value.
float calculate_luminosity(const HSLA& hsla) {
  return (hsla.lightness + hsla.saturation) / 2.0f;
}

// Compares two HSLA pixel values based on their luminosity.
bool compare_hsla_luminosity(const HSLA& hsla1, const HSLA& hsla2) {
  return calculate_luminosity(hsla1) < calculate_luminosity(hsla2);
}

// Radix sort for sorting HSLA pixel values based on luminosity.
void radix_sort_hsla_luminosity(std::vector<HSLA>& list) {
  // Create an array of buckets, one for each luminosity value.
  std::vector<std::vector<HSLA>> buckets(256);

  // Iterate over the list of HSLA pixel values and add each pixel value to the bucket that corresponds to its luminosity.
  for (const HSLA& hsla : list) {
    buckets[static_cast<int>(calculate_luminosity(hsla) * 255.0f)].push_back(hsla);
  }

  // Iterate over the buckets and append the contents of each bucket to the sorted list.
  list.clear();
  for (int i = 0; i < buckets.size(); ++i) {
    list.insert(list.end(), buckets[i].begin(), buckets[i].end());
  }
}

int main(int argc, char **argv) {
    if (argc != 2) {
    std::cout << "random: must specify number" << std::endl;
    return (404);
    }
    int number = atoi(argv[1]);

    auto start{std::chrono::steady_clock::now()};
    auto end{std::chrono::steady_clock::now()};

    start = std::chrono::steady_clock::now();

    std::vector<HSLA> list(number);

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> rand_hue(0.0f, 360.0f);
    std::uniform_real_distribution<> rand_saturation(0.0f, 1.0f);
    std::uniform_real_distribution<> rand_lightness(0.0f, 1.0f);
    std::uniform_real_distribution<> rand_alpha(0.0f, 1.0f);

    for (int i = 0; i < number; ++i) {
    list[i] = {rand_hue(gen), rand_saturation(gen), rand_lightness(gen), rand_alpha(gen)};
    }

    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_init{end - start};

    std::cout << "Initialization time = " << elapsed_seconds_init.count() << "s\n";

    // Sort the list using the std::sort algorithm.
    start = std::chrono::steady_clock::now();
    std::sort(list.begin(), list.end(), compare_hsla_luminosity);
    end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds_sort_std{end - start};
    std::cout << "std::sort time = " << elapsed_seconds_sort_std.count() << "s\n";

    // Sort the list using the radix sort algorithm.
    start = std::chrono::steady_clock::now();
    radix_sort_hsla_luminosity(list);
    end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds_sort_radix{end - start};
    std::cout << "radix sort time = " << elapsed_seconds_sort_radix.count() << "s\n";

    if (elapsed_seconds_sort_std.count() < elapsed_seconds_sort_radix.count()) {
    std::cout << "std::sort is faster" << std::endl;
    } else if (elapsed_seconds_sort_std.count() > elapsed_seconds_sort_radix.count()) {
    std::cout << "Radix sort is faster" << std::endl;
    } else {
    std::cout << "The two sorting algorithms have the same performance" << std::endl;
    }

    std::cout << number << " " << " " << elapsed_seconds_sort_std.count() << " " << elapsed_seconds_sort_radix.count() << std::endl;
    return 0;
}