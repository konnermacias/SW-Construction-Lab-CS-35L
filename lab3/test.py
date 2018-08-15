import argparse

def main():
    parser = argparse.ArgumentParser()

    parser.add_argument('-i', metavar='in-file', type=argparse.FileType('rt'))
    parser.add_argument('-o', metavar='out-file', type=argparse.FileType('wt'))

    try:
        results = parser.parse_args()
        print('Input file:', results.i)
        print('Output file:', results.o)
    except IOError:
        parser.error("fuck me")
    

if __name__ == '__main__':
    main()