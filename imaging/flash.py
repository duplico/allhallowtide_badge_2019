import sys
import os
import subprocess
import click

prepend_src = """@1800
%02X 00 00 00 00 00 00 00
"""
@click.command()
@click.option('-s', '--source-image', 'image_src', required=True, type=click.File('r'), help="TI TXT source image file.")
@click.option('-i', '--id', 'badge_id', required=True, type=int, help="Badge ID to apply")
@click.option('-d', '--dest', 'image_dest', default='tmp.txt', type=click.Path(dir_okay=False, writable=True, allow_dash=True), help="The TI TXT destination file.")
def create_image(image_src, badge_id, image_dest):
    ti_txt_out = ""
    prepend = prepend_src % badge_id
    ti_txt_out = prepend
    for line in image_src:
        ti_txt_out += line
    with open(image_dest, 'w') as tmp_out:
        tmp_out.write(ti_txt_out)

if __name__ == "__main__":
    create_image()