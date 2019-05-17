import numpy as np
import tensorflow as tf
import random

# https://gist.github.com/awjuliani/4d69edad4d0ed9a5884f3cdcf0ea0874#file-q-net-learning-clean-ipynb

lr = 0.5

inputs1 = tf.placeholder(shape=[13, 50], dtype=tf.float32)
W = tf.Variable(tf.random_uniform([50, 2], 0, 0.01))
Qout = tf.matmul(inputs1, w)
predict = tf.argmax(Qout, 1)

nextQ = tf.placeholder(shape=[13, 2], dtype=tf.float32)
loss = tf.reduce_sum(tf.square(nextQ - Qout))
trainer = tf.train.GradientDescentOptimizer(learning_rate=lr)
updateModel = trainer.minimize(loss)

init = tf.initialize_all_variables()

def run(nn):
    y = 0.99
    e = 0.1
    d = False
    j = 0

    # s is world state
    with tf.Session() as sess:
        sess.run(init)
        s = env.reset()
        a, allQ = sess.run([predict, Qout],feed_dict={inputs1:np.identity(50)[s:s+1]})
        #step environment
        Q1 = sess.run(Qout, feed_dict={inputs1:np.identity(50)[s:s+1]})
        maxQ1 = np.max(Q1)
        targetQ = allQ
        targetQ[0, a[0]] = r + y * maxQ1
        _, W1 = sess.run([updateModel, W], feed_dict={inputs1:np.identity(50)[s:s+1], nextQ:targetQ})
        s = s1
