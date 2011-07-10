#!/usr/bin/env python

from setuptools import setup

import nanotime
# not customary, but if this doesn't work, then why bother installing?


setup(
  name="nanotime",
  version=nanotime.__version__,
  description="nanotime python implementation",
  author="Juan Batiz-Benet",
  author_email="jbenet@cs.stanford.com",
  url="http://github.com/jbenet/nanotime/tree/master/python",
  keywords=["nanotime", "nanosecond", "time precision", "64bit time"],
  packages=["nanotime"],
  install_requires=[],
  license="MIT License"
)
