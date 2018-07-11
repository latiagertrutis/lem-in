# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/26 15:15:45 by mrodrigu          #+#    #+#              #
#    Updated: 2018/07/11 04:18:39 by jagarcia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

for n in {1..10000}
do
#	ants=$(jot -r 1 1 10);
	ants=100;
	nodes=$(jot -r 1 2 1000);
	echo "$ants $nodes"
	./maps/lem-in_gen $ants $nodes > tester_map.map
	echo "=============================inicio================================="
	cat tester_map.map
	echo "=============================fin================================="
	./lem-in tester_map.map
	if [ $? -ne 0 ]; then
    	echo "It crashed!"
    	exit 1
	fi
#	read -p "PUTA"
done
