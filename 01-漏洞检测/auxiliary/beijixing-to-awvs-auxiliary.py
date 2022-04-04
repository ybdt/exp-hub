def txt_to_txt():
    with open("target.txt", "r", encoding="UTF-8") as fr:
        with open("legal-target.txt", "w", encoding="UTF-8") as fw:
            lines = fr.readlines()
            for line_ in lines:
                line = line_.strip()
                arr = line.split("/")
                if len(arr) > 3:
                    line = arr[0] + "/" + arr[1] + "/" + arr[2]
                    fw.write(line + "\n")
                else:
                    fw.write(line + "\n")

txt_to_txt()