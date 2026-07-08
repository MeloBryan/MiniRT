/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:32:18 by bmelo             #+#    #+#             */
/*   Updated: 2026/07/08 15:22:52 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# ifdef __linux__

enum e_input
{
	ESC = 65307,
	UP = 65362,
	DOWN = 65364,
	RIGHT = 65363,
	LEFT = 65361,
	ZERO = 48,
	ONE = 49,
	TWO = 50,
	THREE = 51,
	FOUR = 52,
	FIVE = 53,
	SIX = 54,
	Q = 113,
	W = 119,
	E = 101,
	R = 114,
	T = 116,
	Y = 121,
	A = 97,
	S = 115,
	D = 100,
	F = 102,
	G = 103,
	H = 104,
	MOUSE_LEFT_CLK = 1,
	MOUSE_SCRL_CLK = 2,
	MOUSE_RIGHT_CLK = 3,
	MOUSE_SCRL_UP = 4,
	MOUSE_SCRL_DOWN = 5,
};

# else

enum e_input
{
	ESC = 53,
	UP = 126,
	DOWN = 125,
	LEFT = 123,
	RIGHT = 124,
	ZERO = 29,
	ONE = 18,
	TWO = 19,
	THREE = 20,
	FOUR = 21,
	FIVE = 23,
	SIX = 22,
	Q = 12,
	W = 13,
	E = 14,
	R = 15,
	T = 17,
	Y = 16,
	A = 0,
	S = 1,
	D = 2,
	F = 3,
	G = 5,
	H = 4,
	L = 37,
	MOUSE_LEFT_CLK = 1,
	MOUSE_RIGHT_CLK = 2,
	MOUSE_SCRL_CLK = 3,
	MOUSE_SCRL_DOWN = 4,
	MOUSE_SCRL_UP = 5,
};

# endif

#endif
