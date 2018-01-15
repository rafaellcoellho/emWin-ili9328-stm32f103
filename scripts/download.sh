#!/bin/bash
#
# download.sh
#
# Use this script to fetch the latest checkpatch.pl and cleanfile from GitHub

readonly CHECKPATCH_SCRIPT="checkpatch.pl"
readonly CLEANFILE_SCRIPT="cleanfile"

readonly KERNEL_RAW_URL="https://raw.githubusercontent.com/torvalds/linux/master"
readonly CHECKPATCH_URL="${KERNEL_RAW_URL}/scripts/${CHECKPATCH_SCRIPT}"
readonly CLEANFILE_URL="${KERNEL_RAW_URL}/scripts/${CLEANFILE_SCRIPT}"

for download in "${CHECKPATCH_URL}:${CHECKPATCH_SCRIPT}"; do
	echo "Downloading '${download##*:}'..."
	curl -f "${download%:*}" -s -S -O || \
		exit 1
done

for download in "${CLEANFILE_URL}:${CLEANFILE_SCRIPT}"; do
	echo "Downloading '${download##*:}'..."
	curl -f "${download%:*}" -s -S -O || \
		exit 1
done

chmod 755 "${CHECKPATCH_SCRIPT}"
chmod 755 "${CLEANFILE_SCRIPT}"
