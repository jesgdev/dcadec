/*
 * This file is part of libdcadec.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef EXSS_PARSER_H
#define EXSS_PARSER_H

#include "bitstream.h"

#define exss_err(...)   dca_log(exss, ERROR, __VA_ARGS__)

#define exss_err_once(...)  dca_log_once(exss, ERROR, __VA_ARGS__)

struct exss_parser;

struct exss_asset {
    struct exss_parser  *parser;    ///< Parent context

    int     asset_offset;   ///< Offset to asset data from start of substream
    int     asset_size;     ///< Size of encoded asset data
    int     asset_index;    ///< Audio asset identifier

    int     pcm_bit_res;                ///< PCM bit resolution
    int     max_sample_rate;            ///< Maximum sample rate
    int     nchannels_total;            ///< Total number of channels
    bool    one_to_one_map_ch_to_spkr;  ///< One to one channel to speaker mapping flag
    bool    embedded_stereo;            ///< Embedded stereo flag
    bool    embedded_6ch;               ///< Embedded 6 channels flag
    bool    spkr_mask_enabled;          ///< Speaker mask enabled flag
    int     spkr_mask;                  ///< Loudspeaker activity mask
    int     representation_type;        ///< Representation type

    int     coding_mode;        ///< Coding mode for the asset
    int     extension_mask;     ///< Coding components used in asset

    int     core_offset;    ///< Offset to core component from start of substream
    int     core_size;      ///< Size of core component in extension substream

    int     xbr_offset;     ///< Offset to XBR extension from start of substream
    int     xbr_size;       ///< Size of XBR extension in extension substream

    int     xxch_offset;    ///< Offset to XXCH extension from start of substream
    int     xxch_size;      ///< Size of XXCH extension in extension substream

    int     x96_offset;     ///< Offset to X96 extension from start of substream
    int     x96_size;       ///< Size of X96 extension in extension substream

    int     lbr_offset;     ///< Offset to LBR component from start of substream
    int     lbr_size;       ///< Size of LBR component in extension substream

    int     xll_offset;         ///< Offset to XLL data from start of substream
    int     xll_size;           ///< Size of XLL data in extension substream
    bool    xll_sync_present;   ///< XLL sync word present flag
    int     xll_delay_nframes;  ///< Initial XLL decoding delay in frames
    int     xll_sync_offset;    ///< Number of bytes offset to XLL sync

    int     hd_stream_id;   ///< DTS-HD stream ID
};

struct exss_parser {
    struct dcadec_context   *ctx;   ///< Parent context
    struct bitstream        bits;   ///< Bitstream reader

    int     exss_index;         ///< Extension substream index
    int     exss_size_nbits;    ///< Number of bits for extension substream size
    int     exss_size;          ///< Number of bytes of extension substream

    bool    static_fields_present;  ///< Per stream static fields presence flag
    int     npresents;  ///< Number of defined audio presentations
    int     nassets;    ///< Number of audio assets in extension substream

    bool    mix_metadata_enabled;   ///< Mixing metadata enable flag
    int     nmixoutconfigs;         ///< Number of mixing configurations
    int     nmixoutchs[4];          ///< Speaker layout mask for mixer output channels

    struct exss_asset   *assets;    ///< Audio asset descriptors
};

extern const uint32_t exss_sample_rates[16];

int exss_parse(struct exss_parser *exss, uint8_t *data, int size);
struct dcadec_exss_info *exss_get_info(struct exss_parser *exss) __attribute__((cold));

#endif
