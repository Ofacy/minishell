import csv

add_files = False
# Ouvrir le fichier Minishell.csv en mode lecture
with open('Minishell.csv', 'r') as file:
    # Lire le contenu du fichier CSV
    csv_reader = csv.reader(file)
    
    # Créer une liste pour stocker les données extraites
    donnees_extraites = []
    
    # Parcourir chaque ligne du fichier CSV
    for ligne in csv_reader:
        # Vérifier si la ligne contient "NON GERE"
        if "NON GERE" not in ligne and "(" not in ligne[1] and "\\" not in ligne[1] and "time" not in ligne[1] and " <<< " not in ligne[1] and ligne[1] != "$> :" and ligne[1] != "$> !" and "-HOLA" not in ligne[1] and ";" not in ligne[1] and "-p" not in ligne[1] and "env -i" not in ligne[1]:
            if ligne[1].startswith("                                           !!!!! Contenu du fichier a : "):
                add_files = True
            ligne_sans_premiers_caracteres = ""
            if add_files:
                ligne_sans_premiers_caracteres = "echo Amour Tu es Horrible > a\necho 0123456789 > b\necho Prout > c\n"
            # Enlever les 3 premiers caractères de la ligne
            li = ligne[1].splitlines()
            for element in li:
                ligne_sans_premiers_caracteres += element[3:] + "\n"
            
            # Ajouter l'élément modifié à la liste des données extraites
            donnees_extraites.append(ligne_sans_premiers_caracteres)
    
    # Créer un fichier pour chaque élément extrait
    for i, element in enumerate(donnees_extraites):
        # Générer le nom du fichier en fonction de l'index
        nom_fichier = f"./tests/{i}.sh"
        
        # Ouvrir le fichier en mode écriture
        with open(nom_fichier, 'w') as fichier_sortie:
            # Écrire l'élément dans le fichier
            fichier_sortie.write(element)
    print(f"Wrote {i} elements")

