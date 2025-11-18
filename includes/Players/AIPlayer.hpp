/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AIPlayer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:51:01 by mbatty            #+#    #+#             */
/*   Updated: 2025/11/07 11:08:56 by mbatty           ###   ########.fr       */
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

struct	PossibleMoves
{
	int	move;
	int	heuristic;
	
	std::vector<PossibleMoves>	children;
};

class	AIPlayer : public Player
{
	public:
		AIPlayer(){}
		~AIPlayer(){}

		int	play()
		{
			PossibleMoves	moves;

			findBestMove(moves, game.board().get(Board::Player::PLAYER1), game.board().get(Board::Player::PLAYER2));
			return (moves.children[rand() % 7].move);
		}
		int	findBestMove(PossibleMoves &moves, uint64_t p1, uint64_t p2)
		{

			findBestMoveRec(moves, Board::Player::PLAYER1, 8, p1, p2, 6);
			return (1);
		}
		int	findBestMoveRec(PossibleMoves &moves, Board::Player p, uint8_t move, uint64_t p1, uint64_t p2, int layer)
		{
			if (layer == 0)
				return (0);

			Board	board(p1, p2);
			board.set(p, move);
			board.printDebug(file, layer);
			file << std::endl;

			moves.children.push_back(PossibleMoves());
			moves.children.push_back(PossibleMoves());
			moves.children.push_back(PossibleMoves());
			moves.children.push_back(PossibleMoves());
			moves.children.push_back(PossibleMoves());
			moves.children.push_back(PossibleMoves());
			moves.children.push_back(PossibleMoves());

			moves.children[0].move = findBestMoveRec(moves.children[0], (Board::Player)!(int)p, 0, board.get(Board::Player::PLAYER1), board.get(Board::Player::PLAYER2), layer - 1);
			moves.children[1].move = findBestMoveRec(moves.children[1], (Board::Player)!(int)p, 1, board.get(Board::Player::PLAYER1), board.get(Board::Player::PLAYER2), layer - 1);
			moves.children[2].move = findBestMoveRec(moves.children[2], (Board::Player)!(int)p, 2, board.get(Board::Player::PLAYER1), board.get(Board::Player::PLAYER2), layer - 1);
			moves.children[3].move = findBestMoveRec(moves.children[3], (Board::Player)!(int)p, 3, board.get(Board::Player::PLAYER1), board.get(Board::Player::PLAYER2), layer - 1);
			moves.children[4].move = findBestMoveRec(moves.children[4], (Board::Player)!(int)p, 4, board.get(Board::Player::PLAYER1), board.get(Board::Player::PLAYER2), layer - 1);
			moves.children[5].move = findBestMoveRec(moves.children[5], (Board::Player)!(int)p, 5, board.get(Board::Player::PLAYER1), board.get(Board::Player::PLAYER2), layer - 1);
			moves.children[6].move = findBestMoveRec(moves.children[6], (Board::Player)!(int)p, 6, board.get(Board::Player::PLAYER1), board.get(Board::Player::PLAYER2), layer - 1);

			if (move == 8)
				return (0);

			return (move);
		}
};

#endif
