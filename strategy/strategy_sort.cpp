#include <iostream>
#include <vector>

class SortStrategy {
public:
    virtual ~SortStrategy() {}
    virtual void sort(std::vector<int>& data) = 0;
};

class BubbleSortStrategy : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                }
            }
        }
    }
};

class InsertionSortStrategy : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        int n = data.size();
        for (int i = 1; i < n; i++) {
            int key = data[i];
            int j = i - 1;
            while (j >= 0 && data[j] > key) {
                data[j + 1] = data[j];
                j--;
            }
            data[j + 1] = key;
        }
    }
};

class SelectionSortStrategy : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < n; j++) {
                if (data[j] < data[min_idx]) {
                    min_idx = j;
                }
            }
            std::swap(data[min_idx], data[i]);
        }
    }
};

class SortingContext {
public:
    SortingContext(SortStrategy* strategy) : strategy_(strategy) {}

    void set_strategy(SortStrategy* strategy) {
        strategy_ = strategy;
    }

    void sort(std::vector<int>& data) {
        strategy_->sort(data);
    }

private:
    SortStrategy* strategy_;
};

int main() {
    std::vector<int> data = {5, 2, 7, 1, 3, 8, 6, 4};
    BubbleSortStrategy bubble_sort;
    InsertionSortStrategy insertion_sort;
    SelectionSortStrategy selection_sort;

    SortingContext sorting_context(&bubble_sort);
    sorting_context.sort(data);

    sorting_context.set_strategy(&insertion_sort);
    sorting_context.sort(data);

    sorting_context.set_strategy(&selection_sort);
    sorting_context.sort(data);

    return 0;
}
