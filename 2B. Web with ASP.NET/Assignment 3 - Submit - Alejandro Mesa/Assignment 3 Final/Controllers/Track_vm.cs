﻿using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Assignment_3_Final.Controllers
{
    public class Track_vm
    {
    }
    public class TrackBase
    {
        [Key]
        public int TrackId { get; set; }

        [Display(Name = "Track Name")]
        public String Name { get; set; }

        [Display(Name = "Album Identifier")]
        public int? AlbumId { get; set; }

        public int MediaTypeId { get; set; }

        [Display(Name = "Genre")]
        public int? GenreId { get; set; }

        [Display(Name = "Composer Name(s)")]
        public String Composer { get; set; }

        [Display(Name = "Track Length in Milliseconds")]
        public int MilliSeconds { get; set; }

        public int? Bytes { get; set; }

        [Display(Name = "Selling Price")]
        public Double UnitPrice { get; set; }
    }
}