/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:21:01 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/13 02:04:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int main(void)
{
    t_data data;

    // --- TEST 1 : Caméra Valide ---
    printf("--- TEST 1 (Caméra Valide) ---\n");
    ft_bzero(&data, sizeof(t_data));
    parse_camera(" -50.0,0,20 0,0,1 70", &data);
    printf("Flag: %d | Pos: (%f, %f, %f) | Dir: (%f, %f, %f) | FOV: %f\n\n",
           data.camera_already_set, 
           data.cam_pos.x, data.cam_pos.y, data.cam_pos.z,
           data.cam_dir.x, data.cam_dir.y, data.cam_dir.z, 
           data.cam_fov);

    // --- TEST 2 : Erreur format Direction ---
    printf("--- TEST 2 (Erreur: Direction tronquée) ---\n");
    ft_bzero(&data, sizeof(t_data));
    parse_camera(" 0,0,0 1,0 70", &data); // Manque le Z de la direction
    printf("\n");

    // --- TEST 3 : Erreur vecteur de direction hors bornes [-1, 1] ---
    printf("--- TEST 3 (Erreur: Direction > 1) ---\n");
    ft_bzero(&data, sizeof(t_data));
    parse_camera(" 0,0,0 0,2.5,0 90", &data); // Le Y vaut 2.5, c'est interdit
    printf("\n");

    // --- TEST 4 : Erreur FOV négatif ou trop grand ---
    printf("--- TEST 4 (Erreur: FOV > 180) ---\n");
    ft_bzero(&data, sizeof(t_data));
    parse_camera(" 0,0,0 0,0,1 185", &data); // FOV à 185
    printf("\n");

    return (0);
}