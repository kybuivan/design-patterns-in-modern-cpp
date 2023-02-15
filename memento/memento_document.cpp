#include <iostream>
#include <string>
#include <vector>

// Originator class
class Document {
public:
    Document(std::string name) : name_(name) {}

    void set_content(const std::string& content) {
        content_ = content;
    }

    std::string get_content() const {
        return content_;
    }

    // Save current state of the Document object
    std::vector<std::string> save_state() {
        return { name_, content_ };
    }

    // Restore state of the Document object to a previous state
    void restore_state(const std::vector<std::string>& state) {
        name_ = state[0];
        content_ = state[1];
    }

private:
    std::string name_;
    std::string content_;
};

// Caretaker class
class DocumentHistory {
public:
    // Save the state of the Document object
    void save(Document& document) {
        history_.push_back(document.save_state());
    }

    // Restore the state of the Document object to a previous state
    void undo(Document& document) {
        if (history_.empty()) {
            std::cout << "Nothing to undo." << std::endl;
            return;
        }

        const auto state = history_.back();
        document.restore_state(state);
        history_.pop_back();
    }

private:
    std::vector<std::vector<std::string>> history_;
};

// Client code
int main() {
    Document document("My Document");
    DocumentHistory history;

    // Edit the document and save its state
    document.set_content("This is the initial content.");
    history.save(document);

    // Edit the document again and save its state
    document.set_content("This is the modified content.");
    history.save(document);

    // Undo the last change
    history.undo(document);

    // Print the current content of the document
    std::cout << "Current content: " << document.get_content() << std::endl;

    return 0;
}
