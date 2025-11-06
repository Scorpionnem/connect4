/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AIPlayer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:51:01 by mbatty            #+#    #+#             */
/*   Updated: 2025/11/06 11:51:24 by mbatty           ###   ########.fr       */
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

class	AIPlayer : public Player
{
	public:
		AIPlayer(){}
		~AIPlayer(){}

		int	play()
		{
			return (rand() % 7);
		}
};

#endif
