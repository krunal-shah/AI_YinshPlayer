from game import Game
import random
import sys
import time

class RandomPlayer:

	def __init__(self):
		data = sys.stdin.readline().strip().split() # Initialize Environment
		self.player = int(data[0]) - 1 # player can have values 0 and 1
		self.n = int(data[1]) # n can have values 5, 6, or 7
		self.time_left = int(data[2])
		self.game = Game(self.n)
		self.RingPos = {}
		self.play()

	# def placeRing(self):
	# 	movetype = 'P'
	# 	hexagon = random.randint(0,self.n)
	# 	position = random.randint(0,max(0,6*hexagon-1))
	# 	if hexagon==self.n and position%self.n==0:
	# 		position+=1
	# 	return '{type} {hex} {pos}'.format(type=movetype, hex=hexagon, pos=position), len(self.RingPos), hexagon, position

	# def selectRing(self):
	# 	movetype = 'S'
	# 	ring_num = random.randint(0,self.n-1)
	# 	while ring_num not in self.RingPos:
	# 		ring_num = random.randint(0,self.n-1)
	# 	ring = self.RingPos[ring_num]
	# 	return '{type} {hex} {pos}'.format(type=movetype, hex=ring[0], pos=ring[1]), ring_num

	# def moveRing(self):
	# 	movetype = 'M'
	# 	hexagon = random.randint(0,self.n)
	# 	position = random.randint(0,max(0,6*hexagon-1))
	# 	if hexagon==self.n and position%self.n==0:
	# 		position+=1
	# 	return '{type} {hex} {pos}'.format(type=movetype, hex=hexagon, pos=position), hexagon, position

	# def removeRowStart(self):
	# 	movetype = 'RS'
	# 	hexagon = random.randint(0,self.n)
	# 	position = random.randint(0,max(0,6*hexagon-1))
	# 	if hexagon==self.n and position%self.n==0:
	# 		position+=1
	# 	return '{type} {hex} {pos}'.format(type=movetype, hex=hexagon, pos=position)

	# def removeRowEnd(self):
	# 	movetype = 'RE'
	# 	hexagon = random.randint(0,self.n)
	# 	position = random.randint(0,max(0,6*hexagon-1))
	# 	if hexagon==self.n and position%self.n==0:
	# 		position+=1
	# 	return '{type} {hex} {pos}'.format(type=movetype, hex=hexagon, pos=position)

	# def removeRing(self):
	# 	movetype = 'X'
	# 	ring_num = random.randint(0,self.n-1)
	# 	while ring_num not in self.RingPos:
	# 		ring_num = random.randint(0,self.n-1)
	# 	ring = self.RingPos[ring_num]
	# 	return '{type} {hex} {pos}'.format(type=movetype, hex=ring[0], pos=ring[1]), ring_num

	# def play_move_seq(self, move_seq):
	# 	// moves = ' '.join(move_seq) + '\n'
	# 	sys.stdout.write(moves)
	# 	sys.stdout.flush()

	def play(self):
		file = open("game.log", "r")
		lines = file.readlines()
		if self.player == 1:
			move = sys.stdin.readline().strip()
		count = self.player
		sys.stderr.write("move_start " + str(count) + '\n')
		while True: # Keep playing moves till game is over
			move = lines[count].split("\"")[-2]
			sys.stderr.write(move+"\n")
			count+=2
			sys.stdout.write(move+"\n")
			sys.stdout.flush()

			## Execute Other Player Move Sequence
			move = sys.stdin.readline().strip()
			# self.game.execute_move(move)

random_player = RandomPlayer()
