#pragma once

#include <unordered_set>

template<class Button>
class Input {
public:
	void press(Button button) {
		_buttons.insert(button);
	}

	void release(Button button) {
		_buttons.erase(button);
	}

	bool isPressed(Button button) {
		return _buttons.find(button) != _buttons.end();
	}

	bool isPressed() {
		return _buttons.empty() != true;
	}

private:
	std::unordered_set<Button> _buttons;
};