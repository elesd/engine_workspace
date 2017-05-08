import sys
import argparse
import re

g_sourceFilePath = ""
g_moduleName = ''

def writeAndCheckLine(line, out):
    global g_moduleName
    matcher = re.compile("\s*#if\s*ENGINE_USE_" + g_moduleName + "\s*")
    if matcher.match(line):
        out.write("#if !ENGINE_USE_" + g_moduleName + "\n")
    else:
        out.write(line)

def createEmptyFile(path):
    global g_sourceFilePath
    outFilePath = path + "/" + g_sourceFilePath
    with open(outFilePath, 'w') as out:
        with open(g_sourceFilePath, 'r') as f:
            namespaceBracket = False
            ignoreLine = 0
            for line in f:
                if ignoreLine == 0:
                    writeAndCheckLine(line, out)
                if '{' in line and not namespaceBracket:
                    ignoreLine = ignoreLine + 1
                elif '}' in line and ignoreLine > 0:
                    ignoreLine = max(ignoreLine - 1, 0)
                    if ignoreLine == 0:
                        writeAndCheckLine(line, out)

                namespaceBracket = False
                if 'namespace' in line:
                    namespaceBracket = True


def main():
    global g_sourceFilePath
    global g_moduleName
    parser = argparse.ArgumentParser(description='Create empty implementation based on the source file.')
    parser.add_argument('filePath', type=str)
    parser.add_argument('module', choices=['winapi', 'glfw', 'sdl'])
    args = parser.parse_args()
    g_sourceFilePath = args.filePath
    g_moduleName = args.module.upper()
    createEmptyFile("empty")

if __name__ == "__main__":
    main()
