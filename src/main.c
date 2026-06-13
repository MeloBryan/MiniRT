/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:21:01 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/13 02:28:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include <string.h>

// Fonction utilitaire pour réinitialiser la structure de données à chaque test
void reset_data(t_data *data)
{
    ft_bzero(data, sizeof(t_data));
}

int main(void)
{
    t_data data;

    printf("==================================================\n");
    printf("        BANC DE TEST : PARSING MINI RT            \n");
    printf("==================================================\n\n");

    // -----------------------------------------------------------------
    //  SERIE A : AMBIENT LIGHT (A)
    // -----------------------------------------------------------------
    printf("--- [SERIE A] TEST 1 : Ambient Valide ---\n");
    reset_data(&data);
    parse_ambient("A 0.2 255,128,0", &data);
    printf("Résultat -> Ratio: %f | Color: 0x%X\n\n", data.ambient_ratio, data.ambient_color);

    printf("--- [SERIE A] TEST 2 : Ambient Ratio Hors-bornes (> 1) ---\n");
    reset_data(&data);
    parse_ambient("A 1.5 255,255,255", &data);
    printf("\n");

    printf("--- [SERIE A] TEST 3 : Ambient RGB Hors-bornes (> 255) ---\n");
    reset_data(&data);
    parse_ambient("A 0.2 256,0,0", &data);
    printf("\n");


    // -----------------------------------------------------------------
    //  SERIE B : CAMERA (C)
    // -----------------------------------------------------------------
    printf("--------------------------------------------------\n");
    printf("--- [SERIE B] TEST 1 : Camera Valide ---\n");
    reset_data(&data);
    parse_camera("C -50.0,0,20 0,0,1 70", &data);
    printf("Résultat -> Pos: (%f,%f,%f) | Dir: (%f,%f,%f) | FOV: %f\n\n",
        data.cam_pos.x, data.cam_pos.y, data.cam_pos.z,
        data.cam_dir.x, data.cam_dir.y, data.cam_dir.z, data.cam_fov);

    printf("--- [SERIE B] TEST 2 : Camera Direction Hors-bornes (< -1) ---\n");
    reset_data(&data);
    parse_camera("C 0,0,0 -1.2,0,0 70", &data);
    printf("\n");

    printf("--- [SERIE B] TEST 3 : Camera FOV Invalide (> 180) ---\n");
    reset_data(&data);
    parse_camera("C 0,0,0 0,0,1 185", &data);
    printf("\n");


    // -----------------------------------------------------------------
    //  SERIE C : LIGHT (L)
    // -----------------------------------------------------------------
    printf("--------------------------------------------------\n");
    printf("--- [SERIE C] TEST 1 : Light Valide ---\n");
    reset_data(&data);
    parse_light("L -40.0,50.0,0.0 0.6 10,20,30", &data);
    printf("Résultat -> Pos: (%f,%f,%f) | Ratio: %f | Color: 0x%X\n\n",
        data.light_pos.x, data.light_pos.y, data.light_pos.z,
        data.light_ratio, data.light_color);

    printf("--- [SERIE C] TEST 2 : Light Format Tronqué (Manque RGB) ---\n");
    reset_data(&data);
    parse_light("L 0,0,0 0.5", &data);
    printf("\n");


    // -----------------------------------------------------------------
    //  SERIE D : DETECTIONS DES DOUBLONS (FLAGS)
    // -----------------------------------------------------------------
    printf("--------------------------------------------------\n");
    printf("--- [SERIE D] TEST 1 : Doublon de Lumière (L) ---\n");
    reset_data(&data);
    parse_light("L 0,0,0 0.5 255,255,255", &data); // Premier appel OK
    parse_light("L 10,10,10 0.2 0,0,0", &data);     // Deuxième appel -> Doit Error
    printf("\n");

    printf("==================================================\n");
    printf("               FIN DES TESTS                      \n");
    printf("==================================================\n");

    return (0);
}