/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:21:01 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/13 01:29:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
int main(void)
{
    t_data data;

    // --- TEST 1 : Une ligne parfaite ---
    printf("--- TEST 1 (Valide) ---\n");
    ft_bzero(&data, sizeof(t_data));
    parse_ambient(" 0.2 255,128,0", &data);
    printf("Flag set: %d | Ratio: %f | Color: 0x%X\n\n", 
           data.ambient_light_already_set, data.ambient_ratio, data.ambient_color);

    // --- TEST 2 : Espaces et tabulations multiples ---
    printf("--- TEST 2 (Valide avec whitespaces) ---\n");
    ft_bzero(&data, sizeof(t_data));
    parse_ambient("\t 0.7\t\t 0,255,255", &data);
    printf("Flag set: %d | Ratio: %f | Color: 0x%X\n\n", 
           data.ambient_light_already_set, data.ambient_ratio, data.ambient_color);

    // --- TEST 3 : Le doublon (Deux lignes A) ---
    printf("--- TEST 3 (Erreur: Doublon) ---\n");
    ft_bzero(&data, sizeof(t_data));
    parse_ambient(" 0.2 255,255,255", &data);
    parse_ambient(" 0.5 0,0,0", &data); // Doit afficher un message d'erreur
    printf("\n");

    // --- TEST 4 : Ratio hors limite ---
    printf("--- TEST 4 (Erreur: Ratio > 1) ---\n");
    ft_bzero(&data, sizeof(t_data));
    parse_ambient(" 1.5 255,255,255", &data); // Doit afficher un message d'erreur
    printf("\n");

    // --- TEST 5 : RGB invalide (Trop grand) ---\n
    printf("--- TEST 5 (Erreur: RGB > 255) ---\n");
    ft_bzero(&data, sizeof(t_data));
    parse_ambient(" 0.2 256,0,0", &data); // Doit afficher un message d'erreur
    printf("\n");

    // --- TEST 6 : Mauvais nombre d'arguments ---\n
    printf("--- TEST 6 (Erreur: Format cassé) ---\n");
    ft_bzero(&data, sizeof(t_data));
    parse_ambient(" 0.2 255,255", &data); // Manque le bleu, doit afficher une erreur
    printf("\n");

    return (0);
}
