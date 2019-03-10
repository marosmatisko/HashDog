#pragma once

constexpr int alphabet_size = 26;
constexpr int char_count = 80;
constexpr int specials_size = 18;
constexpr int pointer_size = 7;

static const char all_symbols[char_count] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
											  'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
											  'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
											  'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
											  'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
											  'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7',
											  '8', '9', ' ', ',', '-', '_', '.', '?', '!', '&',
											  '@', '#', '$', '%', '^', '*', ':', '~', '{', '}' };

static const char lowercase[alphabet_size] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
											   'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
											   'u', 'v', 'w', 'x', 'y', 'z' };

static const char uppercase[alphabet_size] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
											   'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
											   'U', 'V', 'W', 'X', 'Y', 'Z' };

static const char alphabet[2 * alphabet_size] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
												'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
												'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
												'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
												'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
												'Y', 'Z' };

static const char special_characters[specials_size] = { ' ', ',', '-', '_', '.', '?', '!', '&', '@', '#',
														'$', '%', '^', '*', ':', '~', '{', '}' };
