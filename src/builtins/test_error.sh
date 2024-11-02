#!/bin/bash

echo "=== Test 1: Commande inexistante ==="
./minishell << EOF
inexistant_command
echo \$?
EOF

echo -e "\n=== Test 2: Fichier sans permission ==="
touch test_file
chmod 000 test_file
./minishell << EOF
./test_file
echo \$?
EOF

echo -e "\n=== Test 3: Exécuter un dossier ==="
mkdir -p test_dir
./minishell << EOF
./test_dir
echo \$?
EOF

echo -e "\n=== Test 4: Fichier inexistant ==="
./minishell << EOF
./fichier_inexistant
echo \$?
EOF

# Nettoyage
rm -f test_file
rm -rf test_dir
