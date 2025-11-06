/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Board.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:02:49 by mbatty            #+#    #+#             */
/*   Updated: 2025/11/06 13:27:15 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_HPP
# define BOARD_HPP

# include <cstdint>
# include <iostream>

# include "Window.hpp"

extern Window window;

class	Board
{
	public:
		/*
			Enum used when accessing tiles from the board
		*/
		enum class	Player
		{
			PLAYER1,
			PLAYER2,
		};

	private:
		static constexpr uint64_t	EMPTY_BOARD = 0ULL;
		static constexpr uint8_t	PLAYER1 = 0;
		static constexpr uint8_t	PLAYER2 = 1;
		static constexpr uint8_t	MAX_PLAYERS = 2;

		static constexpr uint8_t	HEIGHT = 6;
		static constexpr uint8_t	WIDTH = 7;

		static constexpr const char	*RED = "\x1b[37;41m";
		static constexpr const char	*BLUE = "\x1b[37;44m";
		static constexpr const char	*RESET = "\x1b[0m";

		uint64_t	_board[Board::MAX_PLAYERS];
	public:
		Board()
		{
			reset();
		}
		Board(uint64_t p1, uint64_t p2)
		{
			_board[Board::PLAYER1] = p1;
			_board[Board::PLAYER2] = p2;
		}
		~Board(){}

		void	reset()
		{
			_board[Board::PLAYER1] = Board::EMPTY_BOARD;
			_board[Board::PLAYER2] = Board::EMPTY_BOARD;
		}

		void	print()
		{
			for (int y = 0; y < Board::HEIGHT; y++)
			{
				for (int x = 0; x < Board::WIDTH; x++)
				{
					if (get(Player::PLAYER1, x, y))
						window.putSquare(x * Window::SQUARE_SIZE, y * Window::SQUARE_SIZE, 0x00770000);
					else if (get(Player::PLAYER2, x, y))
						window.putSquare(x * Window::SQUARE_SIZE, y * Window::SQUARE_SIZE, 0x00000077);
					else if ((x + y) % 2)
						window.putSquare(x * Window::SQUARE_SIZE, y * Window::SQUARE_SIZE, 0x00111111);
				}
			}
		}

		bool	checkWin(Player player)
		{
			bool	ret = false;
			int	color = 0x000000FF;
			if (player ==  Player::PLAYER1)
				color = 0x00FF0000;
			for (int y = 0; y < Board::HEIGHT; y++)
			{
				for (int x = 0; x < Board::WIDTH; x++)
				{
					if (get(player, x, y) && get(player, x + 1, y) && get(player, x + 2, y) && get(player, x + 3, y))
					{
						window.putSquare(x * Window::SQUARE_SIZE, y * Window::SQUARE_SIZE, color);
						window.putSquare((x + 1) * Window::SQUARE_SIZE, (y + 0) * Window::SQUARE_SIZE, color);
						window.putSquare((x + 2) * Window::SQUARE_SIZE, (y + 0) * Window::SQUARE_SIZE, color);
						window.putSquare((x + 3) * Window::SQUARE_SIZE, (y + 0) * Window::SQUARE_SIZE, color);
						ret = true;
					}
					if (get(player, x, y) && get(player, x, y + 1) && get(player, x, y + 2) && get(player, x, y + 3))
					{
						window.putSquare(x * Window::SQUARE_SIZE, y * Window::SQUARE_SIZE, color);
						window.putSquare((x + 0) * Window::SQUARE_SIZE, (y + 1) * Window::SQUARE_SIZE, color);
						window.putSquare((x + 0) * Window::SQUARE_SIZE, (y + 2) * Window::SQUARE_SIZE, color);
						window.putSquare((x + 0) * Window::SQUARE_SIZE, (y + 3) * Window::SQUARE_SIZE, color);
						ret = true;
					}
					if (get(player, x, y) && get(player, x + 1, y + 1) && get(player, x + 2, y + 2) && get(player, x + 3, y + 3))
					{
						window.putSquare(x * Window::SQUARE_SIZE, y * Window::SQUARE_SIZE, color);
						window.putSquare((x + 1) * Window::SQUARE_SIZE, (y + 1) * Window::SQUARE_SIZE, color);
						window.putSquare((x + 2) * Window::SQUARE_SIZE, (y + 2) * Window::SQUARE_SIZE, color);
						window.putSquare((x + 3) * Window::SQUARE_SIZE, (y + 3) * Window::SQUARE_SIZE, color);
						ret = true;
					}
					if (get(player, x, y) && get(player, x - 1, y - 1) && get(player, x - 2, y - 2) && get(player, x - 3, y - 3))
					{
						window.putSquare(x * Window::SQUARE_SIZE, y * Window::SQUARE_SIZE, color);
						window.putSquare((x - 1) * Window::SQUARE_SIZE, (y - 1) * Window::SQUARE_SIZE, color);
						window.putSquare((x - 2) * Window::SQUARE_SIZE, (y - 2) * Window::SQUARE_SIZE, color);
						window.putSquare((x - 3) * Window::SQUARE_SIZE, (y - 3) * Window::SQUARE_SIZE, color);
						ret = true;
					}
					if (get(player, x, y) && get(player, x - 1, y + 1) && get(player, x - 2, y + 2) && get(player, x - 3, y + 3))
					{
						window.putSquare(x * Window::SQUARE_SIZE, y * Window::SQUARE_SIZE, color);
						window.putSquare((x - 1) * Window::SQUARE_SIZE, (y + 1) * Window::SQUARE_SIZE, color);
						window.putSquare((x - 2) * Window::SQUARE_SIZE, (y + 2) * Window::SQUARE_SIZE, color);
						window.putSquare((x - 3) * Window::SQUARE_SIZE, (y + 3) * Window::SQUARE_SIZE, color);
						ret = true;
					}
					if (get(player, x, y) && get(player, x + 1, y - 1) && get(player, x + 2, y - 2) && get(player, x + 3, y - 3))
					{
						window.putSquare(x * Window::SQUARE_SIZE, y * Window::SQUARE_SIZE, color);
						window.putSquare((x + 1) * Window::SQUARE_SIZE, (y - 1) * Window::SQUARE_SIZE, color);
						window.putSquare((x + 2) * Window::SQUARE_SIZE, (y - 2) * Window::SQUARE_SIZE, color);
						window.putSquare((x + 3) * Window::SQUARE_SIZE, (y - 3) * Window::SQUARE_SIZE, color);
						ret = true;
					}
				}
			}
			return (ret);
		}

		static bool	valid(uint8_t x, uint8_t y)
		{
			return (x >= 0 && x < Board::WIDTH && y >= 0 && y < Board::HEIGHT);
		}
		int	getY(uint8_t x)
		{
			int	y = Board::HEIGHT - 1;

			while (get(Player::PLAYER1, x, y) || get(Player::PLAYER2, x, y))
			{
				y--;
				if (y < 0)
					break ;
			}
			return (y);
		}
		void	set(Player player, uint8_t x)
		{
			set(player, x, getY(x));
		}
		void	set(Player player, uint8_t x, uint8_t y)
		{
			_board[(int)player] |= (1ULL << (x * Board::WIDTH + y));
		}
		int	get(Player player, uint8_t x, uint8_t y)
		{
			if (!valid(x, y))
				return (0);
			return ((_board[(int)player] & (1ULL << (x * Board::WIDTH + y))) > 0);
		}
};

#endif
