#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <future>
#include "fix_point_oo.hpp"

const unsigned int vectorSize = 65536;
//const unsigned int vectorSize = 4; //DEBUG

//create one vector to store dot products for each thread
std::vector<fix_point> threadResults;
// create mutex to lock threadResults vector
std::mutex threadResultMutex;



// function that runs on one single thread
void dotProductThread(std::vector<fix_point>::iterator vec1FirstELement, std::vector<fix_point>::iterator vec1LastElement, std::vector<fix_point>::iterator vec2FirstElement) {
    // ... Computes inner product (i.e. sum of products) of the range [first1, last1) .. last element is excluded
    fix_point dotProduct = std::inner_product(vec1FirstELement, vec1LastElement, vec2FirstElement, fix_point(0.f));

    // create a lock so everything within this scope and below this line is locked (http://stackoverflow.com/questions/4989451/mutex-example-tutorial)
    std::lock_guard<std::mutex> lock(threadResultMutex);

    // add thread results to global threadResults vector
    threadResults.push_back(dotProduct);
}



fix_point dot_product_threads(std::vector<fix_point>& vec1, std::vector<fix_point>& vec2) {
    //how many thread is this implementation able to handle?
    const unsigned int numberOfThreads = std::thread::hardware_concurrency();

    // split vectors in pieces for each thread
    // TODO: implement check if vectors have equal length
    // TODO: if vector length is an odd number, or vectorSize % numberOfThread != 0 this calculation will lead to missing elements
    const unsigned int elementsPerThread = vectorSize / numberOfThreads;

    // create a vector that keeps all the threads
    std::vector<std::thread> threads;

    // create threads
    for(unsigned int i = 0; i < numberOfThreads; i++) {
        threads.push_back(std::thread(
                dotProductThread,
                vec1.begin() + elementsPerThread * i,
                vec1.begin() + elementsPerThread * (i + 1),
                vec2.begin() + elementsPerThread * i
        ));
    }

    // call .join() on every thread within the threads vector to wait until they are finished
    for(auto& thread : threads) {
        thread.join();
    }

    // calculate the sum of the thread results
    return std::accumulate(threadResults.begin(), threadResults.end(), fix_point(0.f));
}



fix_point dotProductAsync(std::vector<fix_point>::iterator vec1FirstELement, std::vector<fix_point>::iterator vec1LastElement, std::vector<fix_point>::iterator vec2FirstElement) {
    // ... Computes inner product (i.e. sum of products) of the range [first1, last1) .. last element is excluded
    return std::inner_product(vec1FirstELement, vec1LastElement, vec2FirstElement, fix_point(0.f));
}



fix_point dot_product_async(std::vector<fix_point>& vec1, std::vector<fix_point>& vec2) {

    const unsigned int numberOfFutures = 4;

    // split vectors in pieces for each future
    // TODO: implement check if vectors have equal length
    // TODO: if vector length is an odd number, or vectorSize % numberOfThread != 0 this calculation will lead to missing elements
    const unsigned int elementsPerFuture = vectorSize / numberOfFutures;

    // create a vector that keeps all the futures
    std::vector<std::future<fix_point>> futures;

    // create futures
    for(unsigned int i = 0; i < numberOfFutures; i++) {
        futures.push_back(std::async(
                dotProductAsync,
                vec1.begin() + elementsPerFuture * i,
                vec1.begin() + elementsPerFuture * (i + 1),
                vec2.begin() + elementsPerFuture * i
        ));
    }

    // wait and collect results out of all futures
    fix_point result(0.f);
    for (auto& future : futures)
        result += future.get();

    return result;
}



int main() {
    std::vector<fix_point> vector1;
    std::vector<fix_point> vector2;
    vector1.insert(vector1.begin(), vectorSize, fix_point(0.5f));
    vector2.insert(vector2.begin(), vectorSize, fix_point(0.25f));
//    vector1.insert(vector1.begin(), vectorSize, fix_point(3.f)); //DEBUG
//    vector2.insert(vector2.begin(), vectorSize, fix_point(4.f)); //DEBUG

    auto threadsT1 = std::chrono::high_resolution_clock::now();
    fix_point resultThreads = dot_product_threads(vector1, vector2);
    auto threadsT2 = std::chrono::high_resolution_clock::now();
    auto threadsDuration = std::chrono::duration_cast<std::chrono::microseconds>(threadsT2 - threadsT1).count();
    std::cout << "THREADED dot product = " << resultThreads.to_float() << " (" << threadsDuration << "ms)" << std::endl;

    auto asyncT1 = std::chrono::high_resolution_clock::now();
    fix_point resultAsync = dot_product_async(vector1, vector2);
    auto asyncT2 = std::chrono::high_resolution_clock::now();
    auto asyncDuration = std::chrono::duration_cast<std::chrono::microseconds>(asyncT2 - asyncT1).count();
    std::cout << "ASYNC dot product = " << resultAsync.to_float() << " (" << asyncDuration << "ms)" << std::endl;
}

