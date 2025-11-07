/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AIPlayer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:51:01 by mbatty            #+#    #+#             */
/*   Updated: 2025/11/07 10:56:28 by mbatty           ###   ########.fr       */
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

class	AIPlayer : public Player
{
	public:
		AIPlayer(){}
		~AIPlayer(){}

		int	play()
		{
			findBestMove(game.board().get(Board::Player::PLAYER1), game.board().get(Board::Player::PLAYER2));
			return (rand() % 7);
		}
		int	findBestMove(uint64_t p1, uint64_t p2)
		{
			findBestMoveRec(Board::Player::PLAYER1, 8, p1, p2, 6);
			return (1);
		}
		int	findBestMoveRec(Board::Player p, uint8_t move, uint64_t p1, uint64_t p2, int layer)
		{
			if (layer == 0)
				return (0);

			Board	board(p1, p2);
			board.set(p, move);
				
			findBestMoveRec((Board::Player)!(int)p, 0, board.get(Board::Player::PLAYER1), board.get(Board::Player::PLAYER2), layer - 1);
			findBestMoveRec((Board::Player)!(int)p, 1, board.get(Board::Player::PLAYER1), board.get(Board::Player::PLAYER2), layer - 1);
			findBestMoveRec((Board::Player)!(int)p, 2, board.get(Board::Player::PLAYER1), board.get(Board::Player::PLAYER2), layer - 1);
			findBestMoveRec((Board::Player)!(int)p, 3, board.get(Board::Player::PLAYER1), board.get(Board::Player::PLAYER2), layer - 1);
			findBestMoveRec((Board::Player)!(int)p, 4, board.get(Board::Player::PLAYER1), board.get(Board::Player::PLAYER2), layer - 1);
			findBestMoveRec((Board::Player)!(int)p, 5, board.get(Board::Player::PLAYER1), board.get(Board::Player::PLAYER2), layer - 1);
			findBestMoveRec((Board::Player)!(int)p, 6, board.get(Board::Player::PLAYER1), board.get(Board::Player::PLAYER2), layer - 1);

			if (move == 8)
				return (0);

			board.printDebug(file, layer);
			file << std::endl;

			return (1);
		}
};

#endif
