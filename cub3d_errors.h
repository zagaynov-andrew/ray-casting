/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_errors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 12:54:22 by nforce            #+#    #+#             */
/*   Updated: 2021/01/29 18:43:59 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ERRORS_H
# define CUB3D_ERRORS_H

# include "libs/libft/libft.h"

# define SUCCESS				0
# define ERR_ABS_START_POS		134//"Absence of starting position of the player"
# define ERR_REP_START_POS		135//"Repeated starting position of the player"
# define ERR_EXTRA_CHAR_BETWEEN	136//"Extra characters between configurations. The configurations should be listed first then the map"
# define ERR_NO_MAP				137//"No map at the end of file"
# define ERR_EMPTY_LINE_MAP		138//"Empty line in the map"
# define ERR_NO_COMMA			139//"No comma between the color components"
# define ERR_RE_CONFIG			140//"Re-configuration" ###
# define ERR_EXTRA_CHAR_AFTER	141//"Extra characters after configuration"
# define ERR_RSOLUTION			142//"The screen resolution is not greater than zero in the config \"R\"" #####
# define ERR_EXTEN_TEXTURE		143//"Invalid texture file extension"
# define ERR_TEXTURE_NOT_EXIST	144//"Texture file not exist"
# define ERR_EXTRA_CHAR			145//"Extra character in the configuration" ####
# define ERR_INVALID_COLOR		146//"The color component is not included in the range from 0 to 255"
# define ERR_COLOR_CONFIG		147//"Invalid color format" ####
# define ERR_NO_WALL			148//"The map is not surrounded by walls everywhere"
# define ERR_NO_COLOR			149//"No three components of color"
# define ERR_EXTRA_MAP			150//"Extra character in the map"

 

void	print_error();

#endif