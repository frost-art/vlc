/*****************************************************************************
 * common.h: common definitions
 * Collection of useful common types and macros definitions
 *****************************************************************************
 * Copyright (C) 1998-2005 the VideoLAN team
 * $Id$
 *
 * Authors: Samuel Hocevar <sam@via.ecp.fr>
 *          Vincent Seguin <seguin@via.ecp.fr>
 *          Gildas Bazin <gbazin@videolan.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

/**
 * \file
 * This file is a collection of common definitions and types
 */

/*****************************************************************************
 * Required vlc headers
 *****************************************************************************/
#if defined( _MSC_VER )
#   pragma warning( disable : 4244 )
#endif

#include "vlc_config.h"

/*****************************************************************************
 * Required system headers
 *****************************************************************************/
#include <stdlib.h>
#include <stdarg.h>

#include <string.h>
#include <stdio.h>
#include <inttypes.h>

/*****************************************************************************
 * Basic types definitions
 *****************************************************************************/
#if defined( WIN32 ) || defined( UNDER_CE )
#   include <malloc.h>
#   ifndef PATH_MAX
#       define PATH_MAX MAX_PATH
#   endif
#endif

/* Counter for statistics and profiling */
typedef unsigned long       count_t;

/* DCT elements types */
typedef int16_t             dctelem_t;

/* Video buffer types */
typedef uint8_t             yuv_data_t;

/* Audio volume */
typedef uint16_t            audio_volume_t;

/**
 * High precision date or time interval
 *
 * Store a high precision date or time interval. The maximum precision is the
 * microsecond, and a 64 bits integer is used to avoid overflows (maximum
 * time interval is then 292271 years, which should be long enough for any
 * video). Dates are stored as microseconds since a common date (usually the
 * epoch). Note that date and time intervals can be manipulated using regular
 * arithmetic operators, and that no special functions are required.
 */
typedef int64_t mtime_t;

/**
 * The vlc_fourcc_t type.
 *
 * See http://www.webartz.com/fourcc/ for a very detailed list.
 */
typedef uint32_t vlc_fourcc_t;

#ifdef WORDS_BIGENDIAN
#   define VLC_FOURCC( a, b, c, d ) \
        ( ((uint32_t)d) | ( ((uint32_t)c) << 8 ) \
           | ( ((uint32_t)b) << 16 ) | ( ((uint32_t)a) << 24 ) )
#   define VLC_TWOCC( a, b ) \
        ( (uint16_t)(b) | ( (uint16_t)(a) << 8 ) )

#else
#   define VLC_FOURCC( a, b, c, d ) \
        ( ((uint32_t)a) | ( ((uint32_t)b) << 8 ) \
           | ( ((uint32_t)c) << 16 ) | ( ((uint32_t)d) << 24 ) )
#   define VLC_TWOCC( a, b ) \
        ( (uint16_t)(a) | ( (uint16_t)(b) << 8 ) )

#endif

static inline void __vlc_fourcc_to_char( vlc_fourcc_t fcc, char *psz_fourcc )
{
    memcpy( psz_fourcc, &fcc, 4 );
}

#define vlc_fourcc_to_char( a, b ) \
    __vlc_fourcc_to_char( (vlc_fourcc_t)(a), (char *)(b) )

/*****************************************************************************
 * Classes declaration
 *****************************************************************************/

/* Internal types */
typedef struct libvlc_int_t libvlc_int_t;
typedef struct variable_t variable_t;
typedef struct date_t date_t;
typedef struct dict_entry_t dict_entry_t;
typedef struct dict_t dict_t;
typedef struct gc_object_t gc_object_t ;

/* Messages */
typedef struct msg_subscription_t msg_subscription_t;

/* Playlist */

/* FIXME */
/**
 * Playlist commands
 */
typedef enum {
    PLAYLIST_PLAY,      /**< No arg.                            res=can fail*/
    PLAYLIST_VIEWPLAY,  /**< arg1= playlist_item_t*,*/
                        /**  arg2 = playlist_item_t*          , res=can fail */
    PLAYLIST_PAUSE,     /**< No arg                             res=can fail*/
    PLAYLIST_STOP,      /**< No arg                             res=can fail*/
    PLAYLIST_SKIP,      /**< arg1=int,                          res=can fail*/
} playlist_command_t;


typedef struct playlist_t playlist_t;
typedef struct playlist_item_t playlist_item_t;
typedef struct playlist_view_t playlist_view_t;
typedef struct playlist_export_t playlist_export_t;
typedef struct services_discovery_t services_discovery_t;
typedef struct services_discovery_sys_t services_discovery_sys_t;
typedef struct playlist_add_t playlist_add_t;
typedef struct playlist_preparse_t playlist_preparse_t;
typedef struct playlist_fetcher_t playlist_fetcher_t;

/* Modules */
typedef struct module_bank_t module_bank_t;
typedef struct module_t module_t;
typedef struct module_config_t module_config_t;
typedef struct module_symbols_t module_symbols_t;
typedef struct module_cache_t module_cache_t;

typedef struct config_category_t config_category_t;

/* Interface */
typedef struct intf_thread_t intf_thread_t;
typedef struct intf_sys_t intf_sys_t;
typedef struct intf_console_t intf_console_t;
typedef struct intf_msg_t intf_msg_t;
typedef struct interaction_t interaction_t;
typedef struct interaction_dialog_t interaction_dialog_t;
typedef struct user_widget_t user_widget_t;

/* Input */
typedef struct input_thread_t input_thread_t;
typedef struct input_thread_sys_t input_thread_sys_t;
typedef struct input_item_t input_item_t;
typedef struct access_t access_t;
typedef struct access_sys_t access_sys_t;
typedef struct stream_t     stream_t;
typedef struct stream_sys_t stream_sys_t;
typedef struct demux_t  demux_t;
typedef struct demux_meta_t demux_meta_t;
typedef struct demux_sys_t demux_sys_t;
typedef struct es_out_t     es_out_t;
typedef struct es_out_id_t  es_out_id_t;
typedef struct es_out_sys_t es_out_sys_t;
typedef struct es_descriptor_t es_descriptor_t;
typedef struct seekpoint_t seekpoint_t;
typedef struct info_t info_t;
typedef struct info_category_t info_category_t;
typedef struct input_attachment_t input_attachment_t;

/* Format */
typedef struct audio_format_t audio_format_t;
typedef struct video_format_t video_format_t;
typedef struct subs_format_t subs_format_t;
typedef struct es_format_t es_format_t;
typedef struct video_palette_t video_palette_t;

/* Audio */
typedef struct aout_instance_t aout_instance_t;
typedef struct aout_sys_t aout_sys_t;
typedef struct aout_fifo_t aout_fifo_t;
typedef struct aout_input_t aout_input_t;
typedef struct aout_buffer_t aout_buffer_t;
typedef audio_format_t audio_sample_format_t;
typedef struct audio_date_t audio_date_t;
typedef struct aout_filter_t aout_filter_t;

/* Video */
typedef struct vout_thread_t vout_thread_t;
typedef struct vout_sys_t vout_sys_t;
typedef struct chroma_sys_t chroma_sys_t;

typedef video_format_t video_frame_format_t;
typedef struct picture_t picture_t;
typedef struct picture_sys_t picture_sys_t;
typedef struct picture_heap_t picture_heap_t;

/* Subpictures */
typedef struct spu_t spu_t;
typedef struct subpicture_t subpicture_t;
typedef struct subpicture_sys_t subpicture_sys_t;
typedef struct subpicture_region_t subpicture_region_t;
typedef struct text_style_t text_style_t;

typedef struct image_handler_t image_handler_t;

/* Stream output */
typedef struct sout_instance_t sout_instance_t;
typedef struct sout_instance_sys_t sout_instance_sys_t;

typedef struct sout_input_t sout_input_t;
typedef struct sout_packetizer_input_t sout_packetizer_input_t;

typedef struct sout_access_out_t sout_access_out_t;
typedef struct sout_access_out_sys_t   sout_access_out_sys_t;

typedef struct sout_mux_t sout_mux_t;
typedef struct sout_mux_sys_t sout_mux_sys_t;

typedef struct sout_stream_t    sout_stream_t;
typedef struct sout_stream_sys_t sout_stream_sys_t;

typedef struct config_chain_t       config_chain_t;
typedef struct sap_session_t    sap_session_t;
typedef struct sap_address_t sap_address_t;
typedef struct session_descriptor_t session_descriptor_t;
typedef struct announce_method_t announce_method_t;
typedef struct announce_handler_t announce_handler_t;
typedef struct sap_handler_t sap_handler_t;

typedef struct sout_param_t sout_param_t;
typedef struct sout_pcat_t sout_pcat_t;
typedef struct sout_std_t sout_std_t;
typedef struct sout_display_t sout_display_t;
typedef struct sout_duplicate_t sout_duplicate_t;
typedef struct sout_transcode_t sout_transcode_t;
typedef struct sout_chain_t sout_chain_t;
typedef struct streaming_profile_t streaming_profile_t;
typedef struct sout_module_t sout_module_t;
typedef struct sout_gui_descr_t sout_gui_descr_t;
typedef struct profile_parser_t profile_parser_t;

/* Decoders */
typedef struct decoder_t         decoder_t;
typedef struct decoder_sys_t     decoder_sys_t;
typedef struct decoder_synchro_t decoder_synchro_t;

/* Encoders */
typedef struct encoder_t      encoder_t;
typedef struct encoder_sys_t  encoder_sys_t;

/* Filters */
typedef struct filter_t filter_t;
typedef struct filter_sys_t filter_sys_t;

/* Network */
typedef struct network_socket_t network_socket_t;
typedef struct virtual_socket_t v_socket_t;
typedef struct sockaddr sockaddr;
typedef struct addrinfo addrinfo;
typedef struct vlc_acl_t vlc_acl_t;
typedef struct vlc_url_t vlc_url_t;

/* Misc */
typedef struct iso639_lang_t iso639_lang_t;
typedef struct device_t device_t;
typedef struct device_probe_t device_probe_t;
typedef struct probe_sys_t probe_sys_t;

/* block */
typedef struct block_t      block_t;
typedef struct block_fifo_t block_fifo_t;

/* httpd */
typedef struct httpd_t          httpd_t;
typedef struct httpd_host_t     httpd_host_t;
typedef struct httpd_url_t      httpd_url_t;
typedef struct httpd_client_t   httpd_client_t;
typedef struct httpd_callback_sys_t httpd_callback_sys_t;
typedef struct httpd_message_t  httpd_message_t;
typedef int    (*httpd_callback_t)( httpd_callback_sys_t *, httpd_client_t *, httpd_message_t *answer, const httpd_message_t *query );
typedef struct httpd_file_t     httpd_file_t;
typedef struct httpd_file_sys_t httpd_file_sys_t;
typedef int (*httpd_file_callback_t)( httpd_file_sys_t *, httpd_file_t *, uint8_t *psz_request, uint8_t **pp_data, int *pi_data );
typedef struct httpd_handler_t  httpd_handler_t;
typedef struct httpd_handler_sys_t httpd_handler_sys_t;
typedef int (*httpd_handler_callback_t)( httpd_handler_sys_t *, httpd_handler_t *, char *psz_url, uint8_t *psz_request, int i_type, uint8_t *p_in, int i_in, char *psz_remote_addr, char *psz_remote_host, uint8_t **pp_data, int *pi_data );
typedef struct httpd_redirect_t httpd_redirect_t;
typedef struct httpd_stream_t httpd_stream_t;

/* TLS support */
typedef struct tls_server_t tls_server_t;
typedef struct tls_session_t tls_session_t;

/* Hashing */
typedef struct md5_s md5_t;

/* XML */
typedef struct xml_t xml_t;
typedef struct xml_sys_t xml_sys_t;
typedef struct xml_reader_t xml_reader_t;
typedef struct xml_reader_sys_t xml_reader_sys_t;

/* vod server */
typedef struct vod_t     vod_t;
typedef struct vod_sys_t vod_sys_t;
typedef struct vod_media_t vod_media_t;

/* opengl */
typedef struct opengl_t     opengl_t;
typedef struct opengl_sys_t opengl_sys_t;

/* osdmenu */
typedef struct osd_menu_t   osd_menu_t;
typedef struct osd_state_t  osd_state_t;
typedef struct osd_event_t  osd_event_t;
typedef struct osd_button_t osd_button_t;
typedef struct osd_menu_state_t osd_menu_state_t;

/* VLM */
typedef struct vlm_t         vlm_t;
typedef struct vlm_message_t vlm_message_t;

/* divers */
typedef struct vlc_meta_t    vlc_meta_t;
typedef struct meta_export_t meta_export_t;

/* Stats */
typedef struct counter_t     counter_t;
typedef struct counter_sample_t counter_sample_t;
typedef struct stats_handler_t stats_handler_t;
typedef struct input_stats_t input_stats_t;
typedef struct global_stats_t global_stats_t;

/* Update */
typedef struct update_t update_t;
typedef struct update_iterator_t update_iterator_t;

/* Meta engine */
typedef struct meta_engine_t meta_engine_t;

/* stat/lstat/fstat */
#ifdef WIN32
#include <sys/stat.h>
struct _stati64;
#define stat _stati64
#define fstat _fstati64
/* You should otherwise use utf8_stat and utf8_lstat. */
#else
struct stat;
#endif

/*****************************************************************************
 * Variable callbacks
 *****************************************************************************/
typedef int ( * vlc_callback_t ) ( vlc_object_t *,      /* variable's object */
                                   char const *,            /* variable name */
                                   vlc_value_t,                 /* old value */
                                   vlc_value_t,                 /* new value */
                                   void * );                /* callback data */

/*****************************************************************************
 * Plug-in stuff
 *****************************************************************************/

#if defined (WIN32) && defined (DLL_EXPORT)
#  ifdef __cplusplus
#    define VLC_PUBLIC_API extern "C" __declspec(dllexport)
#    define VLC_PRIVATE_API extern "C" __declspec(dllexport)
#    define   VLC_EXPORT( type, name, args ) extern "C" __declspec(dllexport) type name args
#    define VLC_INTERNAL( type, name, args ) extern "C" type name args
#  else
#    define VLC_PUBLIC_API extern __declspec(dllexport)
#    define VLC_PRIVATE_API extern __declspec(dllexport)
#    define   VLC_EXPORT( type, name, args ) __declspec(dllexport) type name args
#    define VLC_INTERNAL( type, name, args ) type name args
#  endif
#else
#  ifdef __cplusplus
#    ifdef HAVE_ATTRIBUTE_VISIBILITY
#      define VLC_PUBLIC_API extern "C" __attribute__((visibility("default")))
#      define VLC_PRIVATE_API extern "C" __attribute__((visibility("default")))
#      define   VLC_EXPORT( type, name, args ) extern "C" __attribute__((visibility("default"))) type name args
#      define VLC_INTERNAL( type, name, args ) extern "C" __attribute__((visibility("hidden"))) type name args
#    else
#      define VLC_PUBLIC_API extern "C"
#      define   VLC_EXPORT( type, name, args ) extern "C" type name args
#      define VLC_INTERNAL( type, name, args ) extern "C" type name args
#    endif
#  else
#    ifdef HAVE_ATTRIBUTE_VISIBILITY
#      define VLC_PUBLIC_API extern __attribute__((visibility("default")))
#      define VLC_PRIVATE_API extern __attribute__((visibility("default")))
#      define   VLC_EXPORT( type, name, args ) __attribute__((visibility("default"))) type name args
#      define VLC_INTERNAL( type, name, args ) __attribute__((visibility("hidden"))) type name args
#    else
#      define VLC_PUBLIC_API extern
#      define VLC_PRIVATE_API extern
#      define   VLC_EXPORT( type, name, args ) extern type name args
#      define VLC_INTERNAL( type, name, args ) type name args
#    endif
#  endif
#endif

/*****************************************************************************
 * OS-specific headers and thread types
 *****************************************************************************/
#if defined( WIN32 ) || defined( UNDER_CE )
#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#   if defined( UNDER_CE )
#      define IS_WINNT 0
#   else
#      define IS_WINNT ( GetVersion() < 0x80000000 )
#   endif
#endif

#include "vlc_mtime.h"
#include "vlc_threads.h"

typedef struct vlc_object_internals_t vlc_object_internals_t;

/*****************************************************************************
 * Common structure members
 *****************************************************************************/

/* VLC_COMMON_MEMBERS : members common to all basic vlc objects */
#define VLC_COMMON_MEMBERS                                                  \
/** \name VLC_COMMON_MEMBERS                                                \
 * these members are common for all vlc objects                             \
 */                                                                         \
/**@{*/                                                                     \
    int   i_object_id;                                                      \
    int   i_object_type;                                                    \
    const char *psz_object_type;                                            \
    char *psz_object_name;                                                  \
                                                                            \
    /* Messages header */                                                   \
    char *psz_header;                                                       \
    int  i_flags;                                                           \
                                                                            \
    /* Object access lock */                                                \
    vlc_mutex_t  object_lock;                                               \
    vlc_cond_t   object_wait;                                               \
                                                                            \
    /* Object properties */                                                 \
    volatile bool b_error;                  /**< set by the object */ \
    volatile bool b_die;                   /**< set by the outside */ \
    volatile bool b_dead;                   /**< set by the object */ \
    bool b_force;      /**< set by the outside (eg. module_Need()) */ \
                                                                            \
    /* Stuff related to the libvlc structure */                             \
    libvlc_int_t *p_libvlc;                  /**< (root of all evil) - 1 */ \
                                                                            \
    vlc_object_t *  p_parent;                            /**< our parent */ \
                                                                            \
    /* Private data */                                                      \
    void *          p_private;                                              \
                                                                            \
    /** Just a reminder so that people don't cast garbage */                \
    int be_sure_to_add_VLC_COMMON_MEMBERS_to_struct;                        \
/**@}*/                                                                     \

/* VLC_OBJECT: attempt at doing a clever cast */
#define VLC_OBJECT( x ) \
    (((vlc_object_t *)(x))+0*(x)->be_sure_to_add_VLC_COMMON_MEMBERS_to_struct)

#define VLC_GC_MEMBERS                                                       \
/** \name VLC_GC_MEMBERS                                                     \
 * these members are common to all objects that wish to be garbage-collected \
 */                                                                          \
/**@{*/                                                                      \
    int i_gc_refcount;                                                       \
    void (*pf_destructor) ( gc_object_t * );                                 \
    void *p_destructor_arg;                                                  \
/**@}*/

struct gc_object_t
{
            VLC_GC_MEMBERS
};

static inline void __vlc_gc_incref( gc_object_t * p_gc )
{
    p_gc->i_gc_refcount ++;
};

static inline void __vlc_gc_decref( gc_object_t *p_gc )
{
    if( !p_gc ) return;

    p_gc->i_gc_refcount -- ;

    if( p_gc->i_gc_refcount == 0 )
    {
        p_gc->pf_destructor( p_gc );
        /* Do not use the p_gc pointer from now on ! */
    }
}

static inline void
__vlc_gc_init( gc_object_t * p_gc, void (*pf_destructor)( gc_object_t * ),
               void * arg)
{
    p_gc->i_gc_refcount = 1;
    p_gc->pf_destructor = pf_destructor;
    p_gc->p_destructor_arg = arg;
}

#define vlc_gc_incref( a ) __vlc_gc_incref( (gc_object_t *)a )
#define vlc_gc_decref( a ) __vlc_gc_decref( (gc_object_t *)a )
#define vlc_gc_init( a,b,c ) __vlc_gc_init( (gc_object_t *)a,b,c )


/*****************************************************************************
 * Macros and inline functions
 *****************************************************************************/
#ifdef NTOHL_IN_SYS_PARAM_H
#   include <sys/param.h>

#elif !defined(WIN32) && !defined( UNDER_CE )
#   include <netinet/in.h>

#endif /* NTOHL_IN_SYS_PARAM_H || WIN32 */

/* CEIL: division with round to nearest greater integer */
#define CEIL(n, d)  ( ((n) / (d)) + ( ((n) % (d)) ? 1 : 0) )

/* PAD: PAD(n, d) = CEIL(n ,d) * d */
#define PAD(n, d)   ( ((n) % (d)) ? ((((n) / (d)) + 1) * (d)) : (n) )

/* __MAX and __MIN: self explanatory */
#ifndef __MAX
#   define __MAX(a, b)   ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef __MIN
#   define __MIN(a, b)   ( ((a) < (b)) ? (a) : (b) )
#endif

static inline int64_t GCD( int64_t a, int64_t b )
{
    while( b )
    {
        int64_t c = a % b;
        a = b;
        b = c;
    }
    return a;
}

/* function imported from libavutil/common.h */
static inline uint8_t clip_uint8_vlc( int32_t a )
{
    if( a&(~255) ) return (-a)>>31;
    else           return a;
}

/* Malloc with automatic error */
#define MALLOC_VOID( var, type ) do { var = (type*)malloc( sizeof( type) ); \
                                   if( !var ) return; } while(0)
#define MALLOC_NULL( var, type ) do { var = (type*)malloc( sizeof( type) ); \
                                   if( !var ) return NULL; } while(0)
#define MALLOC_ERR( var, type ) do { var = (type*)malloc( sizeof( type) ); \
                                   if( !var ) return VLC_ENOMEM; } while(0)
#define MALLOC_GOTOERR( var, type ) do { var = (type*)malloc( sizeof( type) ); \
                                      if( !var ) goto error; } while(0)
#define DECMALLOC_VOID( var, type ) type* var = (type*)malloc( sizeof(type) );\
                                    if( !var ) return;
#define DECMALLOC_ERR( var, type )  type* var = (type*)malloc( sizeof(type) );\
                                    if( !var ) return VLC_ENOMEM;
#define DECMALLOC_NULL( var, type ) type* var = (type*)malloc( sizeof(type) );\
                                    if( !var ) return NULL;

#define FREENULL(a) do { free( a ); a = NULL; } while(0)

#define EMPTY_STR(str) (!str || !*str)

VLC_EXPORT( char const *, vlc_error, ( int ) );

#include <vlc_arrays.h>

/* MSB (big endian)/LSB (little endian) conversions - network order is always
 * MSB, and should be used for both network communications and files. Note that
 * byte orders other than little and big endians are not supported, but only
 * the VAX seems to have such exotic properties. */
static inline uint16_t U16_AT( const void * _p )
{
    const uint8_t * p = (const uint8_t *)_p;
    return ( ((uint16_t)p[0] << 8) | p[1] );
}
static inline uint32_t U32_AT( const void * _p )
{
    const uint8_t * p = (const uint8_t *)_p;
    return ( ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16)
              | ((uint32_t)p[2] << 8) | p[3] );
}
static inline uint64_t U64_AT( const void * _p )
{
    const uint8_t * p = (const uint8_t *)_p;
    return ( ((uint64_t)p[0] << 56) | ((uint64_t)p[1] << 48)
              | ((uint64_t)p[2] << 40) | ((uint64_t)p[3] << 32)
              | ((uint64_t)p[4] << 24) | ((uint64_t)p[5] << 16)
              | ((uint64_t)p[6] << 8) | p[7] );
}

static inline uint16_t GetWLE( const void * _p )
{
    const uint8_t * p = (const uint8_t *)_p;
    return ( ((uint16_t)p[1] << 8) | p[0] );
}
static inline uint32_t GetDWLE( const void * _p )
{
    const uint8_t * p = (const uint8_t *)_p;
    return ( ((uint32_t)p[3] << 24) | ((uint32_t)p[2] << 16)
              | ((uint32_t)p[1] << 8) | p[0] );
}
static inline uint64_t GetQWLE( const void * _p )
{
    const uint8_t * p = (const uint8_t *)_p;
    return ( ((uint64_t)p[7] << 56) | ((uint64_t)p[6] << 48)
              | ((uint64_t)p[5] << 40) | ((uint64_t)p[4] << 32)
              | ((uint64_t)p[3] << 24) | ((uint64_t)p[2] << 16)
              | ((uint64_t)p[1] << 8) | p[0] );
}

#define GetWBE( p )     U16_AT( p )
#define GetDWBE( p )    U32_AT( p )
#define GetQWBE( p )    U64_AT( p )

/* Helper writer functions */
#define SetWLE( p, v ) _SetWLE( (uint8_t*)(p), v)
static inline void _SetWLE( uint8_t *p, uint16_t i_dw )
{
    p[1] = ( i_dw >>  8 )&0xff;
    p[0] = ( i_dw       )&0xff;
}

#define SetDWLE( p, v ) _SetDWLE( (uint8_t*)(p), v)
static inline void _SetDWLE( uint8_t *p, uint32_t i_dw )
{
    p[3] = ( i_dw >> 24 )&0xff;
    p[2] = ( i_dw >> 16 )&0xff;
    p[1] = ( i_dw >>  8 )&0xff;
    p[0] = ( i_dw       )&0xff;
}
#define SetQWLE( p, v ) _SetQWLE( (uint8_t*)(p), v)
static inline void _SetQWLE( uint8_t *p, uint64_t i_qw )
{
    SetDWLE( p,   i_qw&0xffffffff );
    SetDWLE( p+4, ( i_qw >> 32)&0xffffffff );
}
#define SetWBE( p, v ) _SetWBE( (uint8_t*)(p), v)
static inline void _SetWBE( uint8_t *p, uint16_t i_dw )
{
    p[0] = ( i_dw >>  8 )&0xff;
    p[1] = ( i_dw       )&0xff;
}

#define SetDWBE( p, v ) _SetDWBE( (uint8_t*)(p), v)
static inline void _SetDWBE( uint8_t *p, uint32_t i_dw )
{
    p[0] = ( i_dw >> 24 )&0xff;
    p[1] = ( i_dw >> 16 )&0xff;
    p[2] = ( i_dw >>  8 )&0xff;
    p[3] = ( i_dw       )&0xff;
}
#define SetQWBE( p, v ) _SetQWBE( (uint8_t*)(p), v)
static inline void _SetQWBE( uint8_t *p, uint64_t i_qw )
{
    SetDWBE( p+4,   i_qw&0xffffffff );
    SetDWBE( p, ( i_qw >> 32)&0xffffffff );
}

#define hton16(i) htons(i)
#define hton32(i) htonl(i)
#define ntoh16(i) ntohs(i)
#define ntoh32(i) ntohl(i)

#ifdef WORDS_BIGENDIAN
#   define hton64(i)   ( i )
#   define ntoh64(i)   ( i )
#else
#   define hton64(i)   U64_AT(&i)
#   define ntoh64(i)   U64_AT(&i)
#endif

/* Format string sanity checks */
#ifdef HAVE_ATTRIBUTE_FORMAT
#   define ATTRIBUTE_FORMAT(x,y) __attribute__ ((format(printf,x,y)))
#else
#   define ATTRIBUTE_FORMAT(x,y)
#endif

/* Alignment of critical static data structures */
#ifdef ATTRIBUTE_ALIGNED_MAX
#   define ATTR_ALIGN(align) __attribute__ ((__aligned__ ((ATTRIBUTE_ALIGNED_MAX < align) ? ATTRIBUTE_ALIGNED_MAX : align)))
#else
#   define ATTR_ALIGN(align)
#endif

#ifdef HAVE_ATTRIBUTE_PACKED
#   define ATTR_PACKED __attribute__((__packed__))
#endif

/* */
#define VLC_UNUSED(x) (void)(x)

/* Stuff defined in src/extras/libc.c */
VLC_EXPORT( char *, vlc_strdup, ( const char *s ) );
VLC_EXPORT( int, vlc_vasprintf, (char **, const char *, va_list ) );
VLC_EXPORT( int, vlc_asprintf, (char **, const char *, ... ) ATTRIBUTE_FORMAT( 2, 3 ) );
VLC_EXPORT( char *, vlc_strndup, ( const char *s, size_t n ) );
VLC_EXPORT( size_t, vlc_strlcpy, ( char *, const char *, size_t ) );
VLC_EXPORT( double, vlc_atof, ( const char *nptr ) );
VLC_EXPORT( int64_t, vlc_atoll, ( const char *nptr ) );
VLC_EXPORT( int64_t, vlc_strtoll, ( const char *nptr, char **endptr, int base ) );
VLC_EXPORT( size_t, vlc_strnlen, ( const char *, size_t ) );

#if defined(SYS_BEOS) \
 || (defined (__FreeBSD__) && (__FreeBSD__ < 5))
    typedef struct {
        long long quot; /* Quotient. */
        long long rem;  /* Remainder. */
    } lldiv_t;
#endif
VLC_EXPORT( lldiv_t, vlc_lldiv, ( long long numer, long long denom ) );

struct dirent;
VLC_EXPORT( int, vlc_scandir, ( const char *name, struct dirent ***namelist, int (*filter) ( const struct dirent * ), int (*compar) ( const struct dirent **, const struct dirent ** ) ) );
VLC_EXPORT( int, vlc_alphasort, ( const struct dirent **a, const struct dirent **b ) );

VLC_EXPORT( char *, vlc_getenv, ( const char *name ) );

VLC_EXPORT( int, vlc_strcasecmp, ( const char *s1, const char *s2 ) );
VLC_EXPORT( int, vlc_strncasecmp, ( const char *s1, const char *s2, size_t n ) );
VLC_EXPORT( char *, vlc_strcasestr, ( const char *s1, const char *s2 ) );

#if defined (WIN32)
#   include <dirent.h>
 VLC_INTERNAL( void *, vlc_wopendir, ( const wchar_t * ) );
 VLC_INTERNAL( struct _wdirent *, vlc_wreaddir, ( void * ) );
 VLC_EXPORT( int, vlc_wclosedir, ( void * ) );
 VLC_INTERNAL( void, vlc_rewinddir, ( void * ) );
 VLC_INTERNAL( void, vlc_seekdir, ( void *, long ) );
 VLC_INTERNAL( long, vlc_telldir, ( void * ) );
#   define opendir Use_utf8_opendir_or_vlc_wopendir_instead!
#   define readdir Use_utf8_readdir_or_vlc_wreaddir_instead!
#   define closedir vlc_wclosedir
#   define _wopendir vlc_wopendir
#   define _wreaddir vlc_wreaddir
#   define _wclosedir vlc_wclosedir
#   define rewinddir vlc_rewinddir
#   define seekdir vlc_seekdir
#   define telldir vlc_telldir
#endif

#if defined(WIN32) || defined(UNDER_CE)
/* win32, cl and icl support */
#   if defined( _MSC_VER ) || !defined( __MINGW32__ )
#       define __attribute__(x)
#       define __inline__      __inline
#       define S_IFBLK         0x3000  /* Block */
#       define S_ISBLK(m)      (0)
#       define S_ISCHR(m)      (0)
#       define S_ISFIFO(m)     (((m)&_S_IFMT) == _S_IFIFO)
#       define S_ISREG(m)      (((m)&_S_IFMT) == _S_IFREG)
#   endif

/* several type definitions */
#   if defined( __MINGW32__ )
#       if !defined( _OFF_T_ )
            typedef long long _off_t;
            typedef _off_t off_t;
#           define _OFF_T_
#       else
#           ifdef off_t
#               undef off_t
#           endif
#           define off_t long long
#       endif
#   endif

#   if defined( _MSC_VER ) && !defined( __WXMSW__ )
#       if !defined( _OFF_T_DEFINED )
            typedef __int64 off_t;
#           define _OFF_T_DEFINED
#       else
            /* for wx compatibility typedef long off_t; */
#           define off_t __int64
#       endif
#   endif

#   if defined( __BORLANDC__ )
#       undef off_t
#       define off_t unsigned __int64
#   endif

#   ifndef O_NONBLOCK
#       define O_NONBLOCK 0
#   endif

#   ifndef alloca
#       define alloca _alloca
#   endif

    /* These two are not defined in mingw32 (bug?) */
#   ifndef snprintf
#       define snprintf _snprintf
#   endif
#   ifndef vsnprintf
#       define vsnprintf _vsnprintf
#   endif

#   include <tchar.h>
#endif

VLC_EXPORT( bool, vlc_ureduce, ( unsigned *, unsigned *, uint64_t, uint64_t, uint64_t ) );

/* vlc_wraptext (defined in src/extras/libc.c) */
#define wraptext vlc_wraptext
VLC_EXPORT( char *, vlc_wraptext, ( const char *, int ) );

/* iconv wrappers (defined in src/extras/libc.c) */
typedef void *vlc_iconv_t;
VLC_EXPORT( vlc_iconv_t, vlc_iconv_open, ( const char *, const char * ) );
VLC_EXPORT( size_t, vlc_iconv, ( vlc_iconv_t, const char **, size_t *, char **, size_t * ) );
VLC_EXPORT( int, vlc_iconv_close, ( vlc_iconv_t ) );

/* execve wrapper (defined in src/extras/libc.c) */
VLC_EXPORT( int, __vlc_execve, ( vlc_object_t *p_object, int i_argc, char *const *pp_argv, char *const *pp_env, const char *psz_cwd, const char *p_in, size_t i_in, char **pp_data, size_t *pi_data ) );
#define vlc_execve(a,b,c,d,e,f,g,h,i) __vlc_execve(VLC_OBJECT(a),b,c,d,e,f,g,h,i)

/*****************************************************************************
 * CPU capabilities
 *****************************************************************************/
#define CPU_CAPABILITY_NONE    0
#define CPU_CAPABILITY_486     (1<<0)
#define CPU_CAPABILITY_586     (1<<1)
#define CPU_CAPABILITY_PPRO    (1<<2)
#define CPU_CAPABILITY_MMX     (1<<3)
#define CPU_CAPABILITY_3DNOW   (1<<4)
#define CPU_CAPABILITY_MMXEXT  (1<<5)
#define CPU_CAPABILITY_SSE     (1<<6)
#define CPU_CAPABILITY_SSE2    (1<<7)
#define CPU_CAPABILITY_ALTIVEC (1<<16)
#define CPU_CAPABILITY_FPU     (1<<31)
VLC_EXPORT( unsigned, vlc_CPU, ( void ) );

typedef void *(*vlc_memcpy_t) (void *tgt, const void *src, size_t n);
typedef void *(*vlc_memset_t) (void *tgt, int c, size_t n);

VLC_EXPORT( void, vlc_fastmem_register, (vlc_memcpy_t cpy, vlc_memset_t set) );
VLC_EXPORT( void *, vlc_memcpy, ( void *, const void *, size_t ) );
VLC_EXPORT( void *, vlc_memset, ( void *, int, size_t ) );

/*****************************************************************************
 * I18n stuff
 *****************************************************************************/
#ifdef WIN32
VLC_EXPORT( char *, vlc_dgettext, ( const char *package, const char *msgid ) );
#endif
VLC_EXPORT( char *, vlc_gettext, ( const char *msgid ) );

/*****************************************************************************
 * libvlc features
 *****************************************************************************/
VLC_EXPORT( const char *, VLC_Version, ( void ) );
VLC_EXPORT( const char *, VLC_CompileBy, ( void ) );
VLC_EXPORT( const char *, VLC_CompileHost, ( void ) );
VLC_EXPORT( const char *, VLC_CompileDomain, ( void ) );
VLC_EXPORT( const char *, VLC_Compiler, ( void ) );
VLC_EXPORT( const char *, VLC_Error, ( int ) );
VLC_EXPORT( const char *, VLC_Changeset, ( void ) );

/*****************************************************************************
 * Additional vlc stuff
 *****************************************************************************/
#include "vlc_messages.h"
#include "vlc_variables.h"
#include "vlc_objects.h"
#include "vlc_modules.h"
#include "vlc_main.h"
#include "vlc_configuration.h"

#if defined( WIN32 ) || defined( UNDER_CE )
#   define DIR_SEP_CHAR '\\'
#   define DIR_SEP "\\"
#   define PATH_SEP_CHAR ';'
#   define PATH_SEP ";"
#else
#   define DIR_SEP_CHAR '/'
#   define DIR_SEP "/"
#   define PATH_SEP_CHAR ':'
#   define PATH_SEP ":"
#endif
