{
    'targets': [
        {
            'target_name': 'node_mpv',
            'sources': ['src/addon.cc'],
            'libraries': ['-lmpv'],
            'cflags': ['-std=c++11'],
            'include_dirs': ["<!(node -e \"require('nan')\")"]
        }
    ]
}
