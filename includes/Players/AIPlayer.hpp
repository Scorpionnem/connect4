/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AIPlayer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:51:01 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/12 11:24:41 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AIPLAYER_HPP
# define AIPLAYER_HPP

# include "Player.hpp"
# include "Board.hpp"
# include <string>
# include <iostream>

# include "Window.hpp"
extern Window window;
# include "Game.hpp"
extern Game game;

extern std::ofstream file;

# include <vector>

int	heuristic(Board board, Board::Player player, int x);

class	AIPlayer : public Player
{
	public:
		AIPlayer(){}
		~AIPlayer(){}

		int	play(Board board, Board::Player you)
		{
			(void)board;(void)you;
			int	best_x = 0;
			int	best_heuristic = 0;
			std::vector<int>	best_positions;

			for (int x = 0; x < Board::WIDTH; x++)
			{
				int	tmp = heuristic(board, you, x);
				if (tmp > best_heuristic)
				{
					best_positions.clear();
					best_heuristic = tmp;
					best_x = x;
				}
				if (tmp == best_heuristic)
					best_positions.push_back(x);
			}
			std::cout << "\033c" << std::endl;
			for (auto x : best_positions)
				std::cout << "Could play here: " << x << std::endl;
			std::cout << std::endl;
			int move = best_positions[rand() % best_positions.size()];
			std::cout << "Will play here: " << move << std::endl;
			return (move);
		}
};

#endif
