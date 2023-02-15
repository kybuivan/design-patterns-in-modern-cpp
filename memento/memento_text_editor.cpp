#include <iostream>
#include <string>
#include <vector>

// Memento class
class EditorMemento {
public:
    explicit EditorMemento(const std::string& text) : text_(text) {}

    std::string getText() const {
        return text_;
    }

private:
    std::string text_;
};

// Originator class
class Editor {
public:
    void setText(const std::string& text) {
        text_ = text;
    }

    std::string getText() const {
        return text_;
    }

    EditorMemento createMemento() const {
        return EditorMemento(text_);
    }

    void restoreMemento(const EditorMemento& memento) {
        text_ = memento.getText();
    }

private:
    std::string text_;
};

// Caretaker class
class History {
public:
    void addMemento(const EditorMemento& memento) {
        mementos_.push_back(memento);
    }

    EditorMemento getMemento(int index) const {
        return mementos_.at(index);
    }

private:
    std::vector<EditorMemento> mementos_;
};

// Client code
int main() {
    Editor editor;
    History history;

    // Edit the text
    editor.setText("First version");
    std::cout << "Current text: " << editor.getText() << std::endl;

    // Save the state
    history.addMemento(editor.createMemento());

    // Edit the text again
    editor.setText("Second version");
    std::cout << "Current text: " << editor.getText() << std::endl;

    // Save the state
    history.addMemento(editor.createMemento());

    // Edit the text one more time
    editor.setText("Third version");
    std::cout << "Current text: " << editor.getText() << std::endl;

    // Restore the previous state
    editor.restoreMemento(history.getMemento(1));
    std::cout << "Current text after restoring previous state: " << editor.getText() << std::endl;

    return 0;
}
