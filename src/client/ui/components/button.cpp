//
// Created by Igor on 2/6/2018.
//

#include "button.hpp"


ui::Button::Button(std::function<void(void)> function,
                   const std::wstring_view &caption,
                   const vec2u &pos, const vec2u &size,
                   const HWND &parent, WORD id)
		: Component(pos, size, parent, id),
		  caption(caption),
		  function(std::move(function)) {

	CreateWindow(L"BUTTON", caption.data(), WS_VISIBLE | WS_CHILD,
	             pos.x, pos.y, size.x, size.y, parent, reinterpret_cast<HMENU>(id), nullptr, nullptr);
}

void ui::Button::handleEvent(Event &event) {
	if (event.getId() == id) {
		function();
		event.consume();
	}
}