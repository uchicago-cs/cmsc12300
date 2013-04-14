#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013
#
# Forked from: https://github.com/sorki/python-mnist
#              (written by Richard Marko)

"""This module provides functions to manipulate the MNIST dataset"""

import os
import struct
import numpy
from PIL import Image

class MNISTImage(object):
    def __init__(self, imgdata, label, rows, cols):
        self.imgdata = numpy.array(imgdata, dtype='uint8')
        self.label = label
        self.rows = rows
        self.cols = cols

    def as_asciiart(self):
        width = self.cols
        render = ''
        for i in range(len(self.imgdata)):
            if i % width == 0: render += '\n'
            if self.imgdata[i] > 200:
                render += ' '
            else:
                render += `self.label`
        return render

    def as_array(self):
        return numpy.array(self.imgdata)

    def distance(self, img2):
        return numpy.linalg.norm(self.imgdata.astype("float") - img2.imgdata)

    def as_image(self):
        a = numpy.reshape(255 - self.imgdata, (self.rows, self.cols))
        return Image.fromarray(a)


class MNISTReader(object):
    LABEL_OFFSET = 8
    IMAGE_OFFSET = 16

    def __init__(self, img_fname, lbl_fname, preload = False):
        with open(lbl_fname, 'rb') as f:
            magic, lsize = struct.unpack(">II", f.read(8))
            if magic != 2049:
                raise ValueError('Magic number mismatch, expected 2049,'
                    'got %d' % magic)

        with open(img_fname, 'rb') as f:
            magic, isize, rows, cols = struct.unpack(">IIII", f.read(16))
            if magic != 2051:
                raise ValueError('Magic number mismatch, expected 2051,'
                    'got %d' % magic)        

        if lsize != isize:
            raise ValueError('# labels != # images (%d != %d)' % (lsize, isize))        


        self.lbl_fname = lbl_fname
        self.img_fname = img_fname
        self.num = lsize
        self.rows = rows
        self.cols = cols
        self.preload = preload

        if preload:
            self.memimages = [img for img in self.__images_from_file(as_array=False)]
        else:
            self.memimages = None

    def __images_from_file(self, as_array):
        i = 0
        
        imgf = open(self.img_fname, 'rb')
        imgf.seek(self.IMAGE_OFFSET)

        lblf = open(self.lbl_fname, 'rb')
        lblf.seek(self.LABEL_OFFSET)

        while i < self.num:
            i+=1
            imgdata, label = self.__read_single_image(imgf, lblf)
            img = MNISTImage(imgdata, label, self.rows, self.cols)
            if as_array:
                yield img.as_array(), img.label
            else:
                yield img

        imgf.close()
        lblf.close()

    def __images_from_mem(self, as_array):
        for img in self.memimages:
            if as_array:
                yield img.as_array(), img.label
            else:
                yield img

    def images(self, as_array=False):
        if self.preload:
            return self.__images_from_mem(as_array)
        else:
            return self.__images_from_file(as_array)
       

    def __read_single_image(self, imgf, lblf):
        imgdata = struct.unpack("B"*self.rows*self.cols, imgf.read(self.rows*self.cols))
        label = struct.unpack("B", lblf.read(1))[0]

        return imgdata, label

    def get_image(self, i):
        if i >= self.num:
            raise ValueError('Image index out of bounds (%d >= %d)' % (i, self.num))

        if self.preload:
            return self.memimages[i]
        else:
            imgf = open(self.img_fname, 'rb')
            imgf.seek(self.IMAGE_OFFSET + i * (self.rows*self.cols))

            lblf = open(self.lbl_fname, 'rb')
            lblf.seek(self.LABEL_OFFSET + i)

            imgdata, label = self.__read_single_image(imgf, lblf)

            imgf.close()
            lblf.close()

            return MNISTImage(imgdata, label, self.rows, self.cols)

