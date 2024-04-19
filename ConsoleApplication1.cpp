#include <iostream>                                                            //code poorly made by Zach Kofoed Q934C652
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>



//function to print page table and frames
void printmemory(const std::vector<int>& memory)
{
    //loop to print memory content
    for (int j = 0; j < memory.size(); ++j) 
    {
        std::cout << memory[j];
        //print comma if not last element
        if (j < memory.size() - 1) 
        {
            std::cout << ", ";
        }
    }
}

//function to simulate LRU page replacement algorithm
int lrupagereplacement(const std::vector<int>& pages, int frames)
{
    //map to store page index
    std::unordered_map<int, int> index;
    //vector to simulate memory
    std::vector<int> memory;
    //counter for page faults
    int faults = 0;

    //loop through pages
    for (int i = 0; i < pages.size(); ++i) 
    {
        //if page exists in memory
        if (index.find(pages[i]) != index.end()) 
        {
            //erase page from memory
            memory.erase(remove(memory.begin(), memory.end(), pages[i]), memory.end());
        }
        else
        {
            //if memory is full, remove least recently used page
            if (memory.size() == frames) 
            {
                index.erase(memory.back());
                memory.pop_back();
            }
            else 
            {
                //increment page faults
                ++faults;
            }
        }
        //insert page into memory
        memory.insert(memory.begin(), pages[i]);
        index[pages[i]] = 0;
        //update page index
        for (int j = 1; j < memory.size(); ++j) 
        {
            ++index[memory[j]];
        }
        //print memory state
        std::cout << "- step " << i + 1 << ": page fault (" << pages[i] << ") - page table: {";
        printmemory(memory);
        std::cout << "}, frames: [";
        printmemory(memory);
        std::cout << "], faults: " << faults << std::endl;
    }
    //print total page faults
    std::cout << "- total page faults: " << faults << std::endl;
    return faults;
}

//function to simulate optimal page replacement algorithm
int optimalpagereplacement(const std::vector<int>& pages, int frames) 
{
    //vector to simulate memory
    std::vector<int> memory;
    //counter for page faults
    int faults = 0;

    //loop through pages
    for (int i = 0; i < pages.size(); ++i) 
    {
        //if page not in memory
        if (find(memory.begin(), memory.end(), pages[i]) == memory.end()) 
        {
            //if memory is full, replace page with farthest next occurrence
            if (memory.size() == frames) 
            {
                ++faults;
                int farthest = -1, farthest_index;
                for (int j = 0; j < memory.size(); ++j) 
                {
                    int next_occurrence = pages.size();
                    for (int k = i + 1; k < pages.size(); ++k) 
                    {
                        if (pages[k] == memory[j]) 
                        {
                            next_occurrence = k;
                            break;
                        }
                    }
                    if (next_occurrence > farthest) 
                    {
                        farthest = next_occurrence;
                        farthest_index = j;
                    }
                }
                memory[farthest_index] = pages[i];     //having issues here...
            }
            else 
            {
                //if memory not full, add page
                memory.push_back(pages[i]);
            }
        }
        //print memory state
        std::cout << "- step " << i + 1 << ": page fault (" << pages[i] << ") - page table: {";
        printmemory(memory);
        std::cout << "}, frames: [";
        printmemory(memory);
        std::cout << "], faults: " << faults << std::endl;
    }
    //print total page faults
    std::cout << "- total page faults: " << faults << std::endl;
    return faults;
}

//function to simulate FIFO page replacement algorithm
int fifopagereplacement(const std::vector<int>& pages, int frames) 
{
    //queue to simulate memory
    std::queue<int> memory;
    //map to track page existence in memory
    std::unordered_map<int, bool> inmemory;
    //counter for page faults
    int faults = 0;

    //loop through pages
    for (int i = 0; i < pages.size(); ++i) 
    {
        //if page not in memory
        if (inmemory.find(pages[i]) == inmemory.end()) 
        {
            //if memory is full, remove oldest page
            if (memory.size() == frames) 
            {
                inmemory.erase(memory.front());
                memory.pop();
            }
            else 
            {
                //increment page faults
                ++faults;
            }
            //add page to memory
            memory.push(pages[i]);
            inmemory[pages[i]] = true;
        }
        //print memory state
        std::cout << "- step " << i + 1 << ": page fault (" << pages[i] << ") - page table: {";
        std::queue<int> temp = memory;
        while (!temp.empty()) 
        {
            std::cout << temp.front();
            temp.pop();
            if (!temp.empty()) 
            {
                std::cout << ", ";
            }
        }
        std::cout << "}, frames: [";
        temp = memory;
        while (!temp.empty()) 
        {
            std::cout << temp.front();
            temp.pop();
            if (!temp.empty()) 
            {
                std::cout << ", ";
            }
        }
        std::cout << "], faults: " << faults << std::endl;
    }
    //print total page faults
    std::cout << "- total page faults: " << faults << std::endl;
    return faults;
}

int main() {
    //test data
    std::vector<int> pages = { 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5 };
    int frames = 4;

    //test LRU algorithm
    std::cout << "for lru algorithm:" << std::endl;
    lrupagereplacement(pages, frames);
    std::cout << std::endl;

    //test optimal algorithm
    std::cout << "for optimal algorithm:" << std::endl;
    optimalpagereplacement(pages, frames);
    std::cout << std::endl;

    //test FIFO algorithm
    std::cout << "for fifo algorithm:" << std::endl;
    fifopagereplacement(pages, frames);
    std::cout << std::endl;

    return 0;
}
