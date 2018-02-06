//
// Created by Igor on 2/6/2018.
//

#include "button.hpp"


ui::Button::Button(const std::wstring_view &caption, const vec2u &pos, const vec2u &size, const HWND &parent, WORD id)
		: Component(pos, size, parent, id),
		  caption(caption) {

	handle = CreateWindow(L"BUTTON", caption.data(), WS_VISIBLE | WS_CHILD | WS_BORDER,
	             pos.x, pos.y, size.x, size.y, parent, reinterpret_cast<HMENU>(id), nullptr, nullptr);
}