/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:57:24 by mbatty            #+#    #+#             */
/*   Updated: 2025/11/06 10:09:56 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
# define PLAYER_HPP

class	Player
{
	public:
		Player(){}
		virtual ~Player(){}

		/*
			Returns wich column the player wants to play
		*/
		virtual int play() = 0;
	private:
};

#endif
