import os
import argparse
from pprint import pprint
import subprocess
from time import time , sleep

def red(_str):
    return '\033[91m' + str(_str) + '\033[0m'

def yellow(_str):
    return '\033[93m' + str(_str) + '\033[0m'

def green(_str):
    return '\033[92m' + str(_str) + '\033[0m'

def blue(_str):
    return '\033[94m' + str(_str) + '\033[0m'

def clear_lines(n):
    print('\033[1A\033[2K'*n, end='')

def get_file_size(file_path):
    return os.path.getsize(file_path)

def delete_file(file_path):
    try:
        os.remove(file_path)
    except OSError as e:
        print(red(f"[Error] {e}"))

def calculate_compression_ratio(original_file, compressed_file):
    original_size = get_file_size(original_file)
    compressed_size = get_file_size(compressed_file)

    if original_size > 0:
        return original_size / compressed_size
    
    print(red(f"[ERROR] {original_file} size is 0 bytes."))
    exit()

class Video:
    def __init__(self, original_video_path: str , block_size , searcharea , keyframeperiod , quantization ):
        self.original_video_path = original_video_path 
        self.block_size = block_size
        self.searcharea = searcharea
        self.keyframeperiod = keyframeperiod
        self.quantization_y , self.quantization_u , self.quantization_v = quantization

        self.time = None
        self.psnr = None
        self.compression_ratio = None

        self.ext = ".gtd"
        self.original_ext = "."+original_video_path.split(".")[-1]
        
        self._videoname = None

    def videoname(self):
        if self._videoname:
            return self._videoname
        return ''.join(self.original_video_path.split(".")[:-1]) + "_b" + str(self.block_size) + "_s" + str(self.searcharea) + "_k" + str(self.keyframeperiod) + "_qy" + str(self.quantization_y) +"_qu" + str(self.quantization_u) + "_qv" + str(self.quantization_v)
    
    def encoding_flags(self):
        return ["-i",self.original_video_path,"-e","-o",self.videoname()+self.ext,"-b",str(self.block_size),"-s",str(self.searcharea),"-k",str(self.keyframeperiod),"-qy",str(self.quantization_y),"-qu",str(self.quantization_u),"-qv",str(self.quantization_v)]

    def decoding_flags(self):
        return ["-i",self.videoname()+self.ext,"-d","-o",self.videoname()+self.original_ext]

    def __str__(self) -> str:
        return self.videoname()
    
    def __repr__(self) -> str:
        return str(self)

FFMPEG_FLAG = ["ffmpeg","-hide_banner","-filter_complex","psnr","-f","null","/dev/null"]
def get_psnr( video :Video ):

    flags = FFMPEG_FLAG[:]
    flags.append("-i")
    flags.append(video.videoname()+video.original_ext)
    flags.append("-i")
    flags.append(video.original_video_path)

    try:
        result = subprocess.run(flags, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        # Access the captured output
        program_output = result.stderr.split("\n")[-2]
        video.psnr = [ g for g in program_output.split(" ") if g.startswith("average") ][0].split(":")[-1]

    except subprocess.CalledProcessError as e:
        print(red(f"[Error] {e}"))
    
def delete_files(video: Video):
    delete_file( video.videoname() + video.ext )
    delete_file( video.videoname() + video.original_ext )

def encode(video: Video, codec):
    try:
        start_time = time()
        subprocess.run(["./"+codec]+video.encoding_flags(), stdout=subprocess.PIPE, stderr=subprocess.PIPE,)
        video.time = time() - start_time
    except subprocess.CalledProcessError as e:
        print(red(f"[Error] {e}"))

def decode(video: Video, codec):
    try:
        subprocess.run(["./"+codec]+video.decoding_flags(), stdout=subprocess.PIPE, stderr=subprocess.PIPE,)
        video.compression_ratio = calculate_compression_ratio( video.original_video_path , video.videoname()+video.ext )
    except subprocess.CalledProcessError as e:
        print(red(f"[Error] {e}"))

def check_input_folder(path,video_list):
    if os.path.exists(path) and os.path.isdir(path):
        pass
    else:
        print(red(f"[ERROR] The directory '{path}' does not exist."))
        return False
    files_in_directory = os.listdir(path)
    all_found = True
    for file_name in video_list:
        if file_name not in files_in_directory:
            print(red(f"[ERROR] File '{file_name}' not found in the directory '{path}'."))
            all_found = False
    if all_found:
        print(green("[INFO] All required files found."))
    else:
        print(red("[ERROR] Not all required files found."))
        return False
    return True

def check_output_folder(path):
    return True

def check_report_file(path):
    return True

def check_codec_file(path):
    if os.path.exists(path):
        pass
    else:
        print(red(f"[ERROR] The file '{path}' does not exist."))
        return False
    return True

def check_delete(val):
    if not( val == True or val == "True" or val == "False"):
        print(yellow(f"[WARN] Auto delete '{val}' isnt boolean. Defaulting to True."))
        return True
    return True if ( val == "True" or val == True ) else False

def gen_array(params):
    if len(params) == 0:
        print(red(f"[ERROR] No params supplied."))
        return None
    if len(params) > 3:
        print(red(f"[ERROR] Too many params supplied."))
        return None
    try:
        p = [ int(i) for i in params ]
    except:
        print(red(f"[ERROR] Parsing '{params}'."))
        return None
    if len(p) == 1:
        p.append(p[0]+1)
    if len(p)==2:
        return list(range( p[0],p[1] ))
    return list(range(p[0],p[1],p[2]))

def check_block_size(params):
    a = gen_array(params)
    if a is None:
        print(red(f"[ERROR] Couldn't generate block size array for '{params}'."))
        return False
    return True , a

def check_searcharea(params):
    a = gen_array(params)
    if a is None:
        print(red(f"[ERROR] Couldn't generate search area array for '{params}'."))
        return False
    return True , a

def check_keyframeperiod(params):
    a = gen_array(params)
    if a is None:
        print(red(f"[ERROR] Couldn't generate key frame period array for '{params}'."))
        return False
    return True , a

def check_quantization(params):
    a = gen_array(params)
    if a is None:
        print(red(f"[ERROR] Couldn't generate quantization array for '{params}'."))
        return False
    
    def filter_q(i,j,k):
        if i <= j and i <= k and j==k:
            return True
        return False
    
    r = [ ( i,j,k ) for j in a for k in a for i in a if filter_q(i,j,k)  ]
    return True , r

def gen_videos( video_list , block_sizes , searchareas , keyframeperiods , quantizations ):
    ret = []
    for video in video_list:
        for block_size in block_sizes:
            for searcharea in searchareas:
                for keyframeperiod in keyframeperiods:
                    for quantization in quantizations:
                        ret.append(Video(video,block_size,searcharea,keyframeperiod,quantization))
    print(green(f"[INFO] Testing {yellow(str(len(ret)))}\033[92m configurations. (around 1 min per each one)"))
    return ret

def run(videos,codec,auto_delte):
    counter = 0
    start_time = time()
    estimation = None

    def print_estimation():
        print("     " + yellow(counter) + green('/') + yellow(len(videos)) + green(" videos processed.") )
        print("     " + yellow(str(counter/len(videos)*100)[0:4]) + yellow('%') + green(" done.") )
        if estimation:
            print("     " + green("Approximately ") + yellow( str(len(videos)*estimation-(time() - start_time))[0:4] ) + green(" seconds remaing."))
        else:
            print("     " + green("No estimation on time yet."))

    for video in videos:
        video_time = time()

        print(green(f"[INFO] Encoding {video}"))
        print_estimation()
        encode(video,codec)
        clear_lines(4)

        print(green(f"[INFO] Decoding {video}"))
        print_estimation()
        decode(video,codec)
        clear_lines(4)

        print(green(f"[INFO] Calculating psnr {video}"))
        print_estimation()
        get_psnr(video)
        clear_lines(4)

        if auto_delte:
            delete_files(video)

        if counter == 0:
            estimation = time() - video_time
        else:
            estimation = (time() - video_time) / counter + estimation / counter * (counter -1)
        counter += 1
    clear_lines(1)

def display(videos,report_path):
    for video in videos:
        print(video)
        print("     Time:",video.time)
        print("     PSNR:",video.psnr)
        print("     CR:",video.compression_ratio)
    with open(report_path, 'w') as file:
        for video in videos:
            file.write( video.videoname() + "," + str(video.time) + "," + str(video.psnr) + "," + str(video.compression_ratio) )

def parse_report(path):
    videos = []
    with open(path, 'r') as file:
        for line in file:
            vls = line.split(",")
            video = Video()
            video._videoname = vls[0]
            video.time = vls[1]
            video.psnr = vls[2]
            video.compression_ratio = vls[3]
            videos.append( video )
    return videos

VIDEO_LIST = ["ducks_take_off_444_720p50.y4m","park_joy_444_720p50.y4m","in_to_tree_444_720p50.y4m","old_town_cross_444_720p50.y4m"]
def main():
    global VIDEO_LIST
    parser = argparse.ArgumentParser(description='Run tests.\n\n For arguments that accept multiple values ( i.e quantization ) they have the following structure:   -arg begin end step    which creates an array starting at begin and ending before end whose elements difer by step.\nIf only one arguments is provided then only that value is tested, if 2 arguments are provided the step is assumed to be equal to 1. ')
    parser.add_argument('input_folder'                                                  ,help='Path to the input folder.'                            )
    parser.add_argument('-o', '--output'                    , default='./'              ,help='Path to the report file. (Relative to input folder)'  )
    parser.add_argument('-r', '--report'                    , default='report.txt'      ,help='Path to the output folder. (Relative to input folder)')
    parser.add_argument('-l', '--load'                      , action='store_true'       ,help='Load results from report skipping reencoding.'        )
    parser.add_argument('-c', '--codec'                     , default='../build/GTD-VC' ,help='Path to the codec binaries.'                          )
    parser.add_argument('-d', '--delete'                    , default=True              ,help='Auto delete  files.'                                  )
    parser.add_argument('-b', '--blocksize'     , nargs='+' , default=["16"]            ,help='Block sizes to test.'                                 )
    parser.add_argument('-s', '--searcharea'    , nargs='+' , default=["16"]            ,help='Search areas sizes to test.'                          )
    parser.add_argument('-k', '--keyframeperiod', nargs='+' , default=["10"]            ,help='Keyframe periods to test.'                            )
    parser.add_argument('-q', '--quantization'  , nargs='+' , default=["0","3","1"]     ,help='Quantization values to test.'                         )
    parser.add_argument('-v', '--videolist'     , nargs='+' , default=VIDEO_LIST        ,help='List of videos  to test.'                             )

    args = parser.parse_args()
    no_erros = True

    video_list = list(args.videolist)
    print(green('[INFO] Video list:'))
    print(green("["))
    [ print("   " + ( green(",") if video != video_list[0] else " ") +yellow(video)) for video in video_list ]
    print(green("]"))

    input_folder = args.input_folder
    input_folder = os.path.abspath(input_folder) +"/"
    print(green("[INFO] Input folder: "+str(input_folder)))
    no_erros &= check_input_folder(input_folder,video_list)

    output_folder = input_folder+args.output
    output_folder = os.path.abspath(output_folder) +"/"
    print(green("[INFO] Output folder: "+str(output_folder)))
    no_erros &= check_output_folder(output_folder)

    report_file = input_folder+args.report
    report_file = os.path.abspath(report_file) +"/"
    print(green("[INFO] Output folder: "+str(report_file)))
    no_erros &= check_report_file(report_file)

    if args.load:
        print(blue('[INFO] Load mode is enabled. Skipping coding steps.'))
        videos = parse_report(report_file)
    else:
        codec = args.codec 
        print(green("[INFO] Codec: "+str(codec)))
        no_erros &= check_codec_file(codec)

        auto_delte = args.delete
        auto_delte = check_delete(auto_delte)
        print(green("[INFO] Auto delete: "+str(auto_delte)))

        block_size = args.blocksize
        e , block_size = check_block_size(block_size)
        no_erros &= e
        print(green("[INFO] Block size: "+str(block_size)))

        searcharea = args.searcharea
        e , searcharea = check_searcharea(searcharea)
        no_erros &= e
        print(green("[INFO] Search area: "+str(searcharea)))

        keyframeperiod = args.keyframeperiod
        e , keyframeperiod = check_keyframeperiod(keyframeperiod)
        no_erros &= e
        print(green("[INFO] KeyFrame Period: "+str(keyframeperiod)))

        quantization = args.quantization
        e , quantization = check_quantization(quantization)
        no_erros &= e
        print(green("[INFO] Quantization: "+str(quantization)))

        if not no_erros:
            print(red("\nErrors found please fix them if you wish to proceed."))
            exit()

        video_list = [ input_folder + v for v in video_list ]

        videos = gen_videos(video_list,block_size,searcharea,keyframeperiod,quantization)
        if not(input("\nDo you wish to proceed: (If yes type yes or y)\n") in ["y","Y","YES","Yes","yes"] ):
            exit()
        clear_lines(2)

        run(videos,codec,auto_delte)
        
    display(videos,report_file)

    print(blue("[SUCCESS] Finished running."))

if __name__ == '__main__':
    main()