# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/26 15:15:45 by mrodrigu          #+#    #+#              #
#    Updated: 2018/06/30 16:53:12 by jagarcia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

for n in {1..10000}
do
#	ants=$(jot -r 1 1 10);
	ants=100;
	nodes=$(jot -r 1 2 1000);
	echo "$ants $nodes"
	./lem-in_gen $ants $nodes > prueba1.map
	echo "=============================inicio================================="
	cat prueba1.map
	echo "=============================fin================================="
	./lem-in prueba1.map
	if [ $? -ne 0 ]; then
    	echo "It crashed!"
    	exit 1
	fi
	read -p "PUTA"
done
