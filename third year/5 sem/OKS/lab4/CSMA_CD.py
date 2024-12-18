import random
import time


class CSMA_CD:
    def __init__(self, channel_busy_probability=0.4, collision_probability=0.6):
        self.channel_busy_probability = channel_busy_probability
        self.collision_probability = collision_probability
        self.is_channel_busy = False

    def listen_channel(self):
        self.is_channel_busy = random.random() < self.channel_busy_probability
        return not self.is_channel_busy

    def detect_collision(self):
        collision_happened = random.random() < self.collision_probability
        return collision_happened

    def delay(self, collision_number):
        delay = 2**(collision_number)
        time.sleep(delay)
        return delay