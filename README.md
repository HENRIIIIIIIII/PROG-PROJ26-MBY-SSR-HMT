# 🎰 Analyseur de Loto

> **Statistique et analyse des numéros joués au loto en C11**

| | |
|---|---|
| **Auteurs** | MBY · SSR · HMT |
| **Langage** | C11 |
| **Compilateur** | GCC (Linux) / MSVC (Windows) |
| **Projet** | PROG-PROJ26-MBY-SSR-HMT |

---

## 📋 Description

Ce programme est un **analyseur statistique de loto** écrit en C. Il permet de :

- **Créer** des configurations de loto personnalisées (plages de numéros, numéros complémentaires)
- **Enregistrer** des tirages passés dans des fichiers texte
- **Analyser** les fréquences d'apparition de chaque numéro
- **Identifier** les numéros les plus et moins gagnants
- **Trier** les numéros par fréquence de tirage
- **Simuler** des tirages aléatoires pour la planification

---

## 📸 Captures d'écran

### Écran d'accueil et menu principal
![Menu Principal](https://github.com/user-attachments/assets/e9446f2c-4f47-4a39-98f9-9bb2d6b56836)

### Analyse statistique
![Statistiques](https://github.com/user-attachments/assets/cfd6b8bd-d563-4b3f-92a8-9b9bdbff56e6)

### Gestion des fichiers et tirages
![Gestion Fichiers](https://github.com/user-attachments/assets/e11a4cf3-8d38-44eb-b0e1-4306545aa796)

---

## 🚀 Installation & Compilation

### Prérequis

- Un compilateur C compatible **C11** (GCC ≥ 8, Clang, ou MSVC)
- Un système de fichiers POSIX (ou Windows avec `_MSC_VER`)

### Compilation sous Linux

```bash
make
```

### Compilation sous Windows (Visual Studio)

Ouvrir le fichier `.sln` dans le dossier `Projet_LOTO/` et compiler via Visual Studio.

### Nettoyage

```bash
make clean
```

---

## 🎮 Utilisation

### Lancer le programme

```bash
make run
# ou
./PROG-PROJ26-MBY-SSR-HMT
```

### Menu principal

| # | Fonctionnalité | Description |
|---|---|---|
| **1** | Insérer une valeur | Ajouter un nouveau numéro tiré |
| **2** | Modifier la dernière valeur | Remplacer le dernier numéro enregistré |
| **3** | Supprimer la dernière valeur | Retirer le dernier numéro enregistré |
| **4** | Valeur la plus gagnante | Numéro apparu le plus fréquemment |
| **5** | Valeur la moins gagnante | Numéro apparu le moins fréquemment |
| **6** | 6 meilleurs numéros | Top 6 des numéros les plus fréquents |
| **7** | 6 moins bons numéros | Bottom 6 des numéros les moins fréquents |
| **8** | Tri des fréquences | Affichage trié de tous les numéros par fréquence |
| **9** | Nombre de tirages | Total des tirages enregistrés |
| **10** | Quitter et sauvegarder | Sauvegarde des données et sortie propre |

### Modules

| Module | Responsabilité |
|---|---|
| `main.c` | Orchestration, boucle principale, menu interactif |
| `constantes.h` | Définition de la structure `Loto`, limites, messages |
| `GestionAffichage.*` | Affichage des statistiques, tri, top/bottom |
| `GestionSaisie.*` | Saisie clavier robuste (entiers, chaînes, caractères) |
| `GestionValeurlotoGagnante.*` | Calcul de fréquence, tri, min/max |
| `GestionFichiersLoto.*` | Sauvegarde/chargement, lecture répertoire |

---

## 🔧 Build system

### Makefile (Linux)

```bash
make              # Compiler
make run          # Compiler et lancer
make clean        # Supprimer les fichiers objets et le binaire
```

---

## 📁 Fichiers de données

Les données sont stockées dans des fichiers texte `.txt` avec le préfixe `log` :

```
logLotoSuisse.txt
logEuroMillions.txt
```

Format : 6 valeurs par ligne, séparées par des espaces.

---

## 👥 Équipe

| Initiales | Rôle |
|---|---|
| **MBY** | Développement |
| **SSR** | Développement |
| **HMT** | Développement |
