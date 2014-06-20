var asInitVals = new Array();

function fnFormatDetails ( nTr )
{
        var aData = oTable.fnGetData( nTr );
            var sOut = '<table cellpadding="5" cellspacing="0" border="0" style="padding-left:50px;">';
                sOut += '<tr><td>Rendering engine:</td><td>'+aData[2]+' '+aData[2]+'</td></tr>';
                    sOut += '<tr><td>Link to source:</td><td>Could provide a link here</td></tr>';
                        sOut += '<tr><td>Extra info:</td><td>And any further details here (images etc)</td></tr>';
                            sOut += '</table>';
                                 
                                     return sOut;
}


jQuery(document).ready(function() {
  jQuery('#table-id tbody tr').click( function () {
    if ( oTable.fnIsOpen(this) ) {
      oTable.fnClose( this );
    } else {
      var aData = oTable.fnGetData( this );
      oTable.fnOpen( this, aData[3], "info_row" );
    }
  } );

  var oTable = jQuery('#table-id').dataTable( {
    "oLanguage": {
        "sSearch": "Filtrage en direct:",
        "sInfo": "Affichage des modules _START_ à _END_ (sur _TOTAL_)",
    },
    "bStateSave": true,
    "bPaginate": false,
    "aaSortingFixed": [[ 0, 'asc' ]],
    "aaSorting": [[ 1, 'asc' ]],
    "bAutoWidth": false,
    "aoColumns": [
            { "bVisible": false },
            null,
            null,
            { "bVisible": false },
            null,
        ],
    "sDom": 'lfr<"giveHeight"t>ip',
    "fnDrawCallback": function ( oSettings ) {
            if ( oSettings.aiDisplay.length == 0 )
            {
                return;
            }
             
            var nTrs = jQuery('tbody tr', oSettings.nTable);
            var iColspan = nTrs[0].getElementsByTagName('td').length;
            var sLastGroup = "";
            for ( var i=0 ; i<nTrs.length ; i++ )
            {
                var iDisplayIndex = oSettings._iDisplayStart + i;
                var sGroup = oSettings.aoData[ oSettings.aiDisplay[iDisplayIndex] ]._aData[0];
                if ( sGroup != sLastGroup )
                {
                    var nGroup = document.createElement( 'tr' );
                    var nCell = document.createElement( 'td' );
                    nCell.colSpan = iColspan;
                    nCell.className = "group";
                    nCell.innerHTML = sGroup;
                    nGroup.appendChild( nCell );
                    nTrs[i].parentNode.insertBefore( nGroup, nTrs[i] );
                    sLastGroup = sGroup;
                }
            }
        },
    });
} );
