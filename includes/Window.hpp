/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:30:27 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/12 10:23:33 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_HPP
# define WINDOW_HPP

extern "C"
{
	# include "mlx.h"
}

# include <exception>
# include <stdexcept>

# define ESCAPE_KEY 65307

class	Window
{
	public:
		struct Image
		{
			void	*data;
			char	*addr;
			int		bits_per_pixel;
			int		line_length;
			int		endian;
			int		width;
			int		height;
		};

		constexpr static int	WIDTH = 350 * 2;
		constexpr static int	HEIGHT = 300 * 2;
		constexpr static int	SQUARE_SIZE = WIDTH / 7;
		constexpr static const char	*NAME = "connect4";
	public:
		Window(){}
		~Window(){}

		static int	closeHook();
		static int	loopHook();
		int	mouseX;
		int	mouseY;
		int	mouseClick;
		static int	mouse_press(int button, int x, int y, Window *win)
		{
			win->mouseX = x;
			win->mouseY = y;
			win->mouseClick = button;
			return (0);
		}
		static int	key_press(int button, Window *win)
		{
			(void)win;
			if (button == ESCAPE_KEY)
				closeHook();
			return (0);
		}
		void	open()
		{
			_mlx = mlx_init();
			if (!_mlx)
				throw std::runtime_error("Failed to init MLX");
			_mlx_win = mlx_new_window(_mlx, Window::WIDTH, Window::HEIGHT, (char*)Window::NAME);
			if (!_mlx_win)
				throw std::runtime_error("Failed to init MLX window");
			_img.data = mlx_new_image(_mlx, Window::WIDTH, Window::HEIGHT);
			if (!_img.data)
				throw std::runtime_error("Failed to create image");
			_img.addr = mlx_get_data_addr(_img.data, &_img.bits_per_pixel, &_img.line_length, &_img.endian);

			mlx_hook(_mlx_win, 17, 0, closeHook, this);
			mlx_loop_hook(_mlx, loopHook, this);
			mlx_mouse_hook(_mlx_win, (int (*)())mouse_press, this);
			mlx_key_hook(_mlx_win, (int (*)())key_press, this);
			mlx_loop(_mlx);
		}
		void	close()
		{
			mlx_loop_end(_mlx);

			mlx_destroy_image(_mlx, _img.data);
			mlx_destroy_window(_mlx, _mlx_win);
			mlx_destroy_display(_mlx);
			free(_mlx);
		}
		void	putPixel(int x, int y, int color)
		{
			char	*dst;

			dst = _img.addr + (y * _img.line_length + x * (_img.bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
		void	putSquare(int x, int y, int color)
		{
			int	cur_x;
			int	cur_y;

			cur_x = 0;
			while (cur_x < SQUARE_SIZE)
			{
				cur_y = 0;
				while (cur_y < SQUARE_SIZE)
				{
					putPixel(cur_x + x, cur_y + y, color);
					cur_y++;
				}
				cur_x++;
			}
		}
		void	putSquareHalf(int x, int y, int color)
		{
			int	cur_x;
			int	cur_y;

			cur_x = 0;
			while (cur_x < SQUARE_SIZE)
			{
				cur_y = 0;
				while (cur_y < SQUARE_SIZE)
				{
					if ((cur_x + x) >= 0 && (cur_x + x) < WIDTH && (cur_y + y) >= 0 && (cur_y + y) < HEIGHT)
						if (((cur_x + x) + (cur_y + y)) % 2)
							putPixel(cur_x + x, cur_y + y, color);
					cur_y++;
				}
				cur_x++;
			}
		}
		void	renderImg()
		{
			mlx_put_image_to_window(_mlx, _mlx_win, _img.data, 0, 0);
		}
		void	resetImg()
		{
			int	x;
			int	y;
				
			y = 0;
			while (y < Window::HEIGHT)
			{
				x = 0;
				while (x < Window::WIDTH)
				{
					putPixel(x, y, 0);
					x++;
				}
				y++;
			}
		}

		void	*getMLX() {return (_mlx);}
		void	*getWMLX() {return (_mlx_win);}
	private:
		void		*_mlx;
		void		*_mlx_win;
		Image		_img;
};

#endif
