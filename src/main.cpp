/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 08:55:37 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/12 14:07:10 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"
#include "Board.hpp"
#include "HumanPlayer.hpp"

/*
	6 height
	7 width

	x x x x x x x
	x x x x x x x
	x x x x x x x
	x x x x x x x
	x x x x x x x
	x x x x x x x
*/

# include "Window.hpp"
Window	window;
Game	game;

int	biggest_alignment(Board board, Board::Player player, int x, int y)
{
	int	biggest = 0;

	int	cur = 0;
	int	xx = x;
	while (xx < Board::WIDTH && board.get(player, xx, y))
	{
		cur++;
		xx++;
	}
	if (cur > biggest)
		biggest = cur;

	cur = 0;
	xx = x;
	while (xx >= 0 && board.get(player, xx, y))
	{
		cur++;
		xx--;
	}
	if (cur > biggest)
		biggest = cur;

	cur = 0;
	int	yy = y;
	while (yy < Board::WIDTH && board.get(player, x, yy))
	{
		cur++;
		yy++;
	}
	if (cur > biggest)
		biggest = cur;

	cur = 0;
	yy = y;
	xx = x;
	while (xx < Board::WIDTH && yy < Board::HEIGHT && board.get(player, xx, yy))
	{
		cur++;
		xx++;
		yy++;
	}
	if (cur > biggest)
		biggest = cur;

	cur = 0;
	yy = y;
	xx = x;
	while (xx >= 0 && yy >= 0 && board.get(player, xx, yy))
	{
		cur++;
		xx--;
		yy--;
	}
	if (cur > biggest)
		biggest = cur;

	cur = 0;
	yy = y;
	xx = x;
	while (xx >= 0 && yy < Board::HEIGHT && board.get(player, xx, yy))
	{
		cur++;
		xx--;
		yy++;
	}
	if (cur > biggest)
		biggest = cur;

	cur = 0;
	yy = y;
	xx = x;
	while (xx < Board::WIDTH && yy >= 0 && board.get(player, xx, yy))
	{
		cur++;
		xx++;
		yy--;
	}
	if (cur > biggest)
	biggest = cur;
	
	x++;
	return (biggest);
}

int	heuristic(Board board, Board::Player player, int x)
{
	int y = board.getY(x);
	(void)board;(void)x;(void)player;(void)y;
	if (y < 0)
		return (-1);

	Board	tmp = board;
	int	before = biggest_alignment(tmp, player, x, y);
	tmp.set(player, x);
	int	after = biggest_alignment(tmp, player, x, y);
	if (after >= 4)
		return (__INT_MAX__ / 2);
	if (after > before)
		return (after);

	return (0);
}

void	Game::loop()
{
	int	x, y;

	window.resetImg();
	_board.print();

	if (_board.checkWin(Board::Player::PLAYER1) || _board.checkWin(Board::Player::PLAYER2))
	{
		window.renderImg();
		return ;
	}

	int	previewX = 0;
	int	playerColor = _player == 0 ? 0x00FF0000 : 0x000000FF;
	mlx_mouse_get_pos(window.getMLX(), window.getWMLX(), &x, &y);

	previewX = (int)(7 * ((float)x / (float)Window::WIDTH));
	window.putSquareHalf(previewX * 2 * 50, _board.getY(previewX) * 2 * 50, playerColor);
	_action = _player == 0 ? _player1->play(_board, (Board::Player)_player) : _player2->play(_board, (Board::Player)_player);
	if (_action != -1 && _board.getY(_action) != -1)
	{
		_board.set((Board::Player)_player, _action);
		_player = !_player;
	}

	window.renderImg();

	std::string	str = "play val: " + std::to_string(heuristic(_board, (Board::Player)_player, previewX)) + " on " + std::to_string(previewX) + "/" + std::to_string(_board.getY(previewX));
	mlx_string_put(window.getMLX(), window.getWMLX(), 0, 16, playerColor, (char*)str.c_str());
	window.mouseX = 0;
	window.mouseY = 0;
	window.mouseClick = 0;
}

int	Window::closeHook()
{
	mlx_loop_end(window.getMLX());
	return (0);
}

int	Window::loopHook()
{
	game.loop();
	return (0);
}

#include <ctime>

int	main(void)
{
	srand(std::time(NULL));
	game.run();

	window.open();

	window.close();
}
