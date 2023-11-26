#ifndef LECTURECSV_H
#define LECTURECSV_H
/**
 * @file lecture_csv.h
 * @brief Ce fichier contient les déclarations et la structures pour lire et travailler avec des données CSV
 * @author Yousra Arroui
 * @date 17/10/2023
*/
#define MAX_PHRASE_LENGTH 600

/**
 * @struct Matrix
 * @brief Représente une matrice csv avec lignes, colonnes, données
*/
typedef struct {
    int rows; /**< Le nombre de lignes dans la matrice. */
    int cols; /**< Le nombre de colonnes dans la matrice. */
    char ***data; /*< Un tableau 2D de chaînes de caractères représentant les données CSV. */
} Matrix;

/**
 * @brief Compte le nombre de lignes dans un fichier CSV.
 *
 * Cette fonction lit un fichier CSV et renvoie le nombre de lignes qu'il contient.
 *
 * @param filename Le chemin vers le fichier CSV.
 * @param matrice Un pointeur vers la structure Matrix pour stocker le résultat.
 */
void countRows(const char *filename,Matrix *matrice);

/**
 * @brief Compte le nombre de colonnes dans un fichier CSV.
 *
 * Cette fonction lit un fichier CSV et renvoie le nombre de colonnes qu'il contient.
 *
 * @param filename Le chemin vers le fichier CSV.
 * @param matrice Un pointeur vers la structure Matrix pour stocker le résultat.
 */
void countCols(const char *filename, Matrix *matrice);

/**
 * @brief Crée une matrice à partir d'un fichier CSV.
 *
 * Cette fonction lit un fichier CSV et crée une structure Matrix pour stocker les données.
 *
 * @param filename Le chemin vers le fichier CSV.
 * @param matrice Un pointeur vers la structure Matrix pour stocker les données.
 */
void createMatrix(const char *filename, Matrix *matrice);

/**
 * @brief Affiche le contenu d'une matrice CSV.
 *
 * Cette fonction affiche les données stockées dans une matrice CSV sur la console.
 *
 * @param matrix La structure Matrix à afficher.
 */
void printMatrix(Matrix *matrix);

/**
 * @brief Libère la mémoire allouée pour une matrice CSV.
 *
 * Cette fonction libère la mémoire utilisée par une matrice CSV, y compris ses données.
 *
 * @param matrix La structure Matrix à libérer.
 */
void freeMatrix(Matrix *matrix);


#endif